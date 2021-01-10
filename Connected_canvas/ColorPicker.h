#pragma once
#include "stdafx.h"

class ColorPicker : public QLabel
{
  Q_OBJECT

public:
  ColorPicker(QWidget* parent);

protected:
  void mouseMoveEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void leaveEvent(QEvent* event) override;

signals:
  void displayHoverColor(QColor);
  void displaySelectedColor(QColor);
  void pickerLeaved();

private:
  QImage* image;
};
