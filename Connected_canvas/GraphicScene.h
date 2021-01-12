#pragma once
#include "stdafx.h"
#include "Requester.h"

class Thread : public QThread
{
public:
  Thread(QWidget* parent, QString roomName);

private:
  QString roomName;
  Requester* req;
};

class GraphicScene : public QGraphicsScene
{
public:
  GraphicScene(QWidget* parent, QPen* userPen);
  void joinedRoom(QString roomName);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
  QWidget* parent;
  QPen* userPen;
  QPointF oldPos;
  QImage* image;
  bool isOldPosNull;

  QString currentRoom;
  void draw(const QPointF currentPos);
};
