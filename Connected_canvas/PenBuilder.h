#pragma once
#include "stdafx.h"
#include "ColorPicker.h"

class PenBuilder : public QWidget
{
  Q_OBJECT

public:
  PenBuilder(QWidget* parent, QPen* pen);
  void setSelecter();
  void setPenSizeFromWheel(int);

public slots:
  void applyHoverColor(QColor);
  void applySelectedColor(QColor);
  void applyPickedLeaved();
  void penSizeChanged(QString);
  void penOpacityChanged(QString);

private:
  QPen* mainPen;
  QColor mainColor;
  QLabel* labelHoverColor;
  QLabel* labelSelectedColor;
  QLineEdit* setPenSize;
  QLineEdit* setPenOpacity;
  int alpha;
};
