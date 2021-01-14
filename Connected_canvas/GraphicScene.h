#pragma once
#include "stdafx.h"
#include "Requester.h"

class Thread : public QThread
{
  Q_OBJECT

public:
  Thread(QWidget* parent, QString roomName, QString userName, QImage* image);

public slots:
  void roomRequest(QString);

private:
  QString imageToB64(QImage image);
  QImage b64ToImage(char* base64Array);

  QString roomName;
  Requester* req;
  int iterator;
  QImage* userImage;
  std::vector<std::pair<QString, int>> userListIterator;
  std::map<QString, QImage> userListImage;
};

class GraphicScene : public QGraphicsScene
{
  Q_OBJECT
public:
  GraphicScene(QWidget* parent, QPen* userPen);
  void joinedRoom(QString roomName, QString userName);

signals:
  void penSizeChanged(int);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
  void wheelEvent(QGraphicsSceneWheelEvent* event) override;

private:
  QWidget* parent;
  QPen* userPen;
  QPointF oldPos;
  QImage* image;
  bool isOldPosNull;

  void draw(const QPointF currentPos);
};
