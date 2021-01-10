#include "Canvas.h"

Canvas::Canvas(QWidget* parent, QPen* new_userPen)
  : QWidget(parent)
{

  userPen = new_userPen;
  isOldPosNull = true;
  painter = new QPainter(this);

  this->resize(1000, 1000);
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
  if (event->buttons() == Qt::LeftButton)
  {
    currentPos = event->pos();
    this->repaint();
  }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
  isOldPosNull = true;
}

void Canvas::paintEvent(QPaintEvent* event)
{
  painter->begin(this);
  painter->restore();
  painter->setPen(*userPen);

  if (isOldPosNull)
  {
    oldPos = currentPos;
  }
  painter->drawLine(oldPos.x(), oldPos.y(), currentPos.x(), currentPos.y());
  painter->save();
  painter->end();
}