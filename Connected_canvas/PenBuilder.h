#pragma once
#include "stdafx.h"
#include "ColorPicker.h"

class PenBuilder : public QWidget
{
  Q_OBJECT

public:
  PenBuilder(QWidget* parent, QPen* pen);
  void setSelecter();

public slots:
  void applyHoverColor(QColor);
  void applySelectedColor(QColor);
  void applyPickedLeaved();

private:
  QPen* mainPen;
  QColor mainColor;
  QLabel* labelHoverColor;
  QLabel* labelSelectedColor;
};
