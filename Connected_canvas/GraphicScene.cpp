#include "GraphicScene.h"

Thread::Thread(QWidget* newParent, QString newRoomName, QString newUserName, QImage* image, int& newIterator, std::map<QString, QImage>& newUserListImage, LayerList* newLayerList) // THREAD
  : QThread(newParent)
{
  iterator = &newIterator;
  roomName = newRoomName;
  userImage = image;
  parent = newParent;
  userName = newUserName;
  userListImage = &newUserListImage;
  layerList = newLayerList;
  request = "";
  listChanged = false;

  connect(this, SIGNAL(finished()), this, SLOT(loopThread()));
  req = new Requester();
  connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(getRequest(QString)));

  this->start();
}

QString Thread::imageToB64(QImage image)
{
  QByteArray byteArray;
  QBuffer buff(&byteArray);
  buff.open(QIODevice::WriteOnly);
  image.save(&buff, "PNG");
  return byteArray.toBase64();
}

QImage Thread::b64ToImage(char* base64Array)
{
  return QImage::fromData(QByteArray::fromBase64(base64Array));
}

void Thread::loopThread()
{
  req->updateRoom(parent, roomName, userName, imageToB64(*userImage), *iterator);
}

void Thread::getRequest(QString newRequest)
{
  request = newRequest;

  if (listChanged)
  {
    layerList->reBuild();
  }
  emit drawFromServer();

  this->start();
}

void Thread::run()
{
  QJsonObject jsonObj((QJsonDocument::fromJson(request.toUtf8()).object()));
  QStringList newUsers = jsonObj.keys();
  QStringList trash;

  listChanged = false;

  int sizeList = int(userListIterator.size());
  for (int i = 0; i < sizeList; i++) // FOR EVERY STOCKED PLAYERS
  {
    if (newUsers.contains(userListIterator.at(i).first)) // CHECK IF STILL IN ROOM
    {
      auto currentUser = jsonObj.value(userListIterator.at(i).first).toObject(); // GET HIS OBJECT
      int currentIterator = currentUser.value("iterator").toString().toInt();
      if (userListIterator.at(i).second != currentIterator) // IF ITERATOR CHANGED
      {
        userListImage->at(userListIterator.at(i).first) = b64ToImage(currentUser.value("map").toString().toUtf8().data()); // IF ITERATOR CHANGES, SET NEW QIMAGE
        userListIterator.at(i).second = currentIterator;
      }
    }
    else
    { // IF AN USER IS NOT ANYMORE IN THE ROOM, HES ADDED DO TRASH
      trash.append(userListIterator.at(i).first);
    }
  }

  for (const QString user : newUsers) // CHECK FROM NEW USERS
  {
    if (userListImage->count(user) == 0) // IF ONE ISN'T IN OLD LIST
    {
      listChanged = true;
      layerList->newUser(user);
      userListIterator.push_back(std::pair<QString, int>(user, 0)); // CREATE NEW USER
      userListImage->insert(std::pair<QString, QImage>(user, b64ToImage(jsonObj.value(user).toObject().value("map").toString().toUtf8().data())));
    }
  }
  for (const QString& userToDelete : trash) // DELETES USERS FROM TRASH
  {
    sizeList = int(userListIterator.size());
    for (int i = 0; i < sizeList; i++)
    {
      if (userListIterator.at(i).first == userToDelete)
      {
        layerList->leavedUser(userListIterator.at(i).first);
        userListIterator.erase(userListIterator.begin() + i);
      }
    }
    userListImage->erase(userToDelete);
    listChanged = true;
  }
  sleep(0.5);
}

GraphicScene::GraphicScene(QWidget* new_parent, QPen* new_userPen, bool* isPainting, LayerList* newLayerList, QGraphicsView* newView) // SCENE
  : QGraphicsScene(new_parent)
{
  parent = new_parent;
  userPen = new_userPen;
  paint = isPainting;
  layerList = newLayerList;
  sortedLayers = newLayerList->getList();
  isOldPosNull = true;
  th = nullptr;
  online = false;
  iterator = 0;
  roomName = "";
  userName = "";
  req = new Requester();
  view = newView;

  drawCursor();
  image = new QImage(1000, 1000, QImage::Format_ARGB32);
  image->fill(Qt::transparent);
  this->addPixmap(QPixmap::fromImage(*image));
}

void GraphicScene::drawCursor()
{
  int width = userPen->width();

  QPen pen(Qt::gray);
  pen.setWidth(2);
  QPixmap pix(width, width);
  pix.fill(Qt::transparent);
  QPainter paint(&pix);
  paint.setPen(pen);

  paint.drawEllipse(0, 0, width, width);

  QCursor cursor = (pix);
  view->setCursor(cursor);
}

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  if (event->buttons() == Qt::LeftButton)
  {
    drawPoint(event->scenePos());
  }
}

void GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  if (event->buttons() == Qt::LeftButton)
  {
    drawLine(event->scenePos());
  }
}

void GraphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  isOldPosNull = true;
}

void GraphicScene::drawPoint(const QPointF currentPos)
{
  QPainter painter(image);
  if (!*paint)
  {
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
  }
  painter.setPen(*userPen);

  if (isOldPosNull)
  {
    oldPos = currentPos;
  }
  painter.drawPoint(currentPos.x(), currentPos.y());
  oldPos = currentPos;
  isOldPosNull = false;

  iterator++;
  fillScene();
}

void GraphicScene::drawLine(const QPointF currentPos)
{
  QPainter painter(image);
  if (!*paint)
  {
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
  }
  painter.setPen(*userPen);

  if (isOldPosNull)
  {
    oldPos = currentPos;
  }
  painter.drawLine(oldPos.x(), oldPos.y(), currentPos.x(), currentPos.y());
  oldPos = currentPos;
  isOldPosNull = false;

  iterator++;
  fillScene();
}

void GraphicScene::joinedRoom(QString newRoomName, QString newUserName)
{
  if (th)
  {
    th->quit();
    req->leaveRoom(parent, roomName, userName);
    userListImage.clear();
    layerList->clearList();
  }
  online = true;
  iterator = 0;
  roomName = newRoomName;
  userName = newUserName;

  th = new Thread(parent, roomName, newUserName, image, iterator, userListImage, layerList);

  connect(th, SIGNAL(drawFromServer()), this, SLOT(fillScene()));
}

void GraphicScene::fillScene()
{
  qDebug() << "test1";
  this->clear();

  int sizeList = int(sortedLayers->size());
  if (!online)
  {
    this->addPixmap(QPixmap::fromImage(*image));
    qDebug() << "test2";
    return;
  }

  for (int i = 0; i < sizeList; i++)
  {
    if (sortedLayers->at(i) == userName)
    {
      this->addPixmap(QPixmap::fromImage(*image));
    }
    else
    {
      this->addPixmap(QPixmap::fromImage(userListImage.at(sortedLayers->at(i))));
    }
  }
  qDebug() << "test2";
}

void GraphicScene::wheelEvent(QGraphicsSceneWheelEvent* event)
{
  if (QGuiApplication::queryKeyboardModifiers() == Qt::ShiftModifier)
  {
    int numDegrees = event->delta() / 8;
    double wheel_height = numDegrees;

    if (wheel_height > 0)
    {
      emit penSizeChanged(1);
    }

    else if (wheel_height < 0)
    {
      emit penSizeChanged(-1);
    }
  }
  else
  {
    QGraphicsScene::wheelEvent(event);
  }
  drawCursor();
}

void GraphicScene::closeThread()
{
  if (th)
  {
    th->quit();
    req->leaveRoom(parent, roomName, userName);
  }
}