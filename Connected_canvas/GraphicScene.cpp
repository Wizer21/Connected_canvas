#include "GraphicScene.h"

Thread::Thread(QWidget* parent, QString newRoomName)
  : QThread(parent)
{
  roomName = newRoomName;
  req = new Requester();
}

GraphicScene::GraphicScene(QWidget* new_parent, QPen* new_userPen)
  : QGraphicsScene(new_parent)
{
  parent = new_parent;
  userPen = new_userPen;
  isOldPosNull = true;
  currentRoom = "";

  image = new QImage(1000, 1000, QImage::Format_RGB32);
  this->setMinimumRenderSize(1000);
}

void GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  if (event->buttons() == Qt::LeftButton)
  {
    draw(event->scenePos());
  }
}

void GraphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  isOldPosNull = true;
}

void GraphicScene::draw(const QPointF currentPos)
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

void GraphicScene::joinedRoom(QString roomName)
{
  currentRoom = roomName;
  Thread th(parent, roomName);
}