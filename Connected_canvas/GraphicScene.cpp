#include "GraphicScene.h"

GraphicScene::GraphicScene(QWidget* parent, QPen* new_userPen)
  : QGraphicsScene(parent)
{
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
    qDebug() << event->pos();
    draw(event->scenePos());
  }
}

void GraphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  isOldPosNull = true;
}

//void GraphicScene::paintEvent(QPaintEvent* event)
//{
//  QPainter painter(this);
//  QRect dirtyRect = event->rect();
//  painter.drawImage(dirtyRect, *image, dirtyRect);
//}

void GraphicScene::draw(const QPointF currentPos)
{
  qDebug() << currentPos;

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
}