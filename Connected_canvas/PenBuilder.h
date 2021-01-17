#pragma once
#include "stdafx.h"
#include "ColorPicker.h"
#include "SUtils.h"

class PenBuilder : public QWidget
{
  Q_OBJECT

public:
  PenBuilder(QWidget* parent, QPen* pen, bool* isPainting);
  void setSelecter();
  void setPenSizeFromWheel(int);

public slots:
  void applyHoverColor(QColor);
  void applySelectedColor(QColor);
  void applyPickedLeaved();
  void penSizeChanged(int);
  void penOpacityChanged(int);
  void drawClicked();

signals:
  void penSizeChanged();

private:
  QPen* mainPen;
  QColor mainColor;
  QLabel* labelHoverColor;
  QLabel* labelSelectedColor;
  QSpinBox* setPenSize;
  QSpinBox* setPenOpacity;
  bool* paint;
  int alpha;
};
