#include "GraphicScene.h"

Thread::Thread(QWidget* newParent, QString newRoomName, QString newUserName, QImage* image, int& newIterator, std::map<QString, QImage>& newUserListImage) // THREAD
  : QThread(newParent)
{
  iterator = &newIterator;
  roomName = newRoomName;
  userImage = image;
  parent = newParent;
  userName = newUserName;
  userListImage = &newUserListImage;

  req = new Requester();
  connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(roomRequest(QString)));

  time = new QTimer();
  connect(time, SIGNAL(timeout()), this, SLOT(newIteration()));
  time->start(500);

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
  QImage img = QImage::fromData(QByteArray::fromBase64(base64Array));
  //img.fill(Qt::transparent);
  return img;
}

void Thread::newIteration()
{
  req->updateRoom(parent, roomName, userName, imageToB64(*userImage), *iterator);

  time->start(500);
}

void Thread::roomRequest(QString request)
{
  QJsonObject jsonObj((QJsonDocument::fromJson(request.toUtf8()).object()));
  QStringList newUsers = jsonObj.keys();
  QStringList trash;

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
      userListIterator.push_back(std::pair<QString, int>(user, 0)); // CREATE NEW USER
      QImage img = b64ToImage(jsonObj.value(user).toObject().value("map").toString().toUtf8().data());
      userListImage->insert(std::pair<QString, QImage>(user, img));
    }
  }
  for (const QString& userToDelete : trash) // DELETES USERS FROM TRASH
  {
    sizeList = int(userListIterator.size());
    for (int i = 0; i < sizeList; i++)
    {
      if (userListIterator.at(i).first == userToDelete)
      {
        userListIterator.erase(userListIterator.begin() + i);
      }
    }
    userListImage->erase(userToDelete);
  }

  emit drawFromServer();
}

GraphicScene::GraphicScene(QWidget* new_parent, QPen* new_userPen) // SCENE
  : QGraphicsScene(new_parent)
{
  parent = new_parent;
  userPen = new_userPen;
  isOldPosNull = true;
  th = nullptr;
  iterator = 0;
  userName = "";

  image = new QImage(1000, 1000, QImage::Format_ARGB32);
  image->fill(Qt::transparent);
  this->addPixmap(QPixmap::fromImage(*image));
  this->setMinimumRenderSize(1000);
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
  painter.setPen(*userPen);

  if (isOldPosNull)
  {
    oldPos = currentPos;
  }
  painter.drawPoint(currentPos.x(), currentPos.y());
  oldPos = currentPos;
  isOldPosNull = false;

  iterator++;
  update();
  fillScene();
}

void GraphicScene::drawLine(const QPointF currentPos)
{
  QPainter painter(image);
  painter.setPen(*userPen);

  if (isOldPosNull)
  {
    oldPos = currentPos;
  }
  painter.drawLine(oldPos.x(), oldPos.y(), currentPos.x(), currentPos.y());
  oldPos = currentPos;
  isOldPosNull = false;

  iterator++;
  update();
  fillScene();
}

void GraphicScene::joinedRoom(QString roomName, QString newUserName)
{
  iterator = 0;
  userListImage.clear();
  userName = newUserName;

  if (th)
  {
    th->quit();
    delete th;
    th = new Thread(parent, roomName, newUserName, image, iterator, userListImage);
  }
  else
  {
    th = new Thread(parent, roomName, newUserName, image, iterator, userListImage);
  }
  connect(th, SIGNAL(drawFromServer()), this, SLOT(fillScene()));
}

void GraphicScene::fillScene()
{
  this->clear();

  for (const auto& it : userListImage)
  {
    if (it.first != userName)
    {
      this->addPixmap(QPixmap::fromImage(it.second));
    }
  }
  this->addPixmap(QPixmap::fromImage(*image));
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
}

void GraphicScene::closeThread()
{
  th->quit();
}