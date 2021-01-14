#include "GraphicScene.h"

Thread::Thread(QWidget* parent, QString newRoomName, QString userName, QImage* image) // THREAD
  : QThread(parent)
{
  iterator = 0;
  roomName = newRoomName;
  userImage = image;

  req = new Requester();
  connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(roomRequest(QString)));
  req->updateRoom(parent, newRoomName, userName, imageToB64(*userImage), iterator);
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
  QByteArray byteArray = QByteArray::fromBase64(base64Array);
  return QImage::fromData(byteArray);
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
      auto currentUser = jsonObj.value(userListIterator.at(i).first).toObject();  // GET HIS OBJECT
      if (userListIterator.at(i).second != currentUser.value("iterator").toInt()) // IF ITERATOR CHANGED
      {
        userListImage.at(userListIterator.at(i).first) = b64ToImage(currentUser.value("map").toString().toUtf8().toBase64().data()); // IF ITERATOR CHANGES, SET NEW QIMAGE
      }
    }
    else
    { // IF AN USER IS NOT ANYMORE IN THE ROOM, HES ADDED DO TRASH
      trash.append(userListIterator.at(i).first);
    }
  }

  for (const QString user : newUsers) // CHECK FROM NEW USERS
  {
    if (!newUsers.contains(user)) // IF ONE ISN'T IN OLD LIST
    {
      userListIterator.push_back(std::pair<QString, int>(user, 0)); // PUSH IT
      userListImage.insert(std::pair<QString, QImage>(user, b64ToImage(jsonObj.value(user).toObject().value("map").toString().toUtf8().toBase64().data())));
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
    userListImage.erase(userToDelete);
  }
}

GraphicScene::GraphicScene(QWidget* new_parent, QPen* new_userPen) // SCENE
  : QGraphicsScene(new_parent)
{
  parent = new_parent;
  userPen = new_userPen;
  isOldPosNull = true;

  image = new QImage(1000, 1000, QImage::Format_RGB32);
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

  update();
  this->clear();
  this->addPixmap(QPixmap::fromImage(*image));
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

  update();
  this->clear();
  this->addPixmap(QPixmap::fromImage(*image));
}

void GraphicScene::joinedRoom(QString roomName, QString userName)
{
  Thread th(parent, roomName, userName, image);
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