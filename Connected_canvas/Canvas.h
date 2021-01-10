#pragma once
#include "stdafx.h"
#include <QDebug>

class Canvas : public QWidget
{
public:
  Canvas(QWidget* parent, QPen* userPen);

protected:
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

private:
  QPen* userPen;
  QPointF oldPos;
  QPointF currentPos;
  QPainter* painter;
  bool isOldPosNull;
};
