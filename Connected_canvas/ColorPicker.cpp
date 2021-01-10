#include "ColorPicker.h"

ColorPicker::ColorPicker(QWidget* parent)
  : QLabel(parent)
{
  this->setMouseTracking(true);
  image = new QImage(":/Connected_canvas/files/IarsV.jpg");
  this->setPixmap(QPixmap(":/Connected_canvas/files/IarsV.jpg"));
}

void ColorPicker::mouseMoveEvent(QMouseEvent* event)
{
  emit displayHoverColor(QColor(image->pixelColor(event->pos())));
  if (event->buttons() == Qt::LeftButton)
  {
    emit displaySelectedColor(QColor(image->pixelColor(event->pos())));
  }
}

void ColorPicker::mousePressEvent(QMouseEvent* event)
{
  if (event->buttons() == Qt::LeftButton)
  {
    emit displaySelectedColor(QColor(image->pixelColor(event->pos())));
  }
}

void ColorPicker::leaveEvent(QEvent* event)
{
  emit pickerLeaved();
}