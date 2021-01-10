#include "Canvas.h"

Canvas::Canvas(QWidget* parent, QPen* new_userPen)
  : QWidget(parent)
{
  setAttribute(Qt::WA_StaticContents);
  userPen = new_userPen;
  isOldPosNull = true;

  image = new QImage(1000, 1000, QImage::Format_RGB32);
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
  if (event->buttons() == Qt::LeftButton)
  {
    draw(event->pos());
  }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
  isOldPosNull = true;
}

void Canvas::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, *image, dirtyRect);
}

void Canvas::draw(const QPointF currentPos)
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
}