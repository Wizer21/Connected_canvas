#pragma once
#include "stdafx.h"
#include <QDebug>

class GraphicScene : public QGraphicsScene
{
public:
  GraphicScene(QWidget* parent, QPen* userPen);
  void joinedRoom(QString roomName);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
  QPen* userPen;
  QPointF oldPos;
  QImage* image;
  bool isOldPosNull;

  QString currentRoom;
  void draw(const QPointF currentPos);
};
