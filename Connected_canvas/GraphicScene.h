#pragma once
#include "stdafx.h"
#include "Requester.h"

class Thread : public QThread
{
  Q_OBJECT

public:
  Thread(QWidget* parent, QString roomName, QString userName, QImage* image, int& iterator, std::map<QString, QImage>& userListImage);

public slots:
  void roomRequest(QString);
  void newIteration();

signals:
  void drawFromServer();

private:
  QString imageToB64(QImage image);
  QImage b64ToImage(char* base64Array);

  QWidget* parent;
  QString userName;
  QString roomName;
  Requester* req;
  int* iterator;
  QImage* userImage;
  QTimer* time;

  std::vector<std::pair<QString, int>> userListIterator;
  std::map<QString, QImage>* userListImage;
};

class GraphicScene : public QGraphicsScene
{
  Q_OBJECT
public:
  GraphicScene(QWidget* parent, QPen* userPen);
  void joinedRoom(QString roomName, QString userName);
  void closeThread();

public slots:
  void fillScene();

signals:
  void penSizeChanged(int);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
  void wheelEvent(QGraphicsSceneWheelEvent* event) override;

private:
  int iterator;
  QString userName;
  QWidget* parent;
  QPen* userPen;
  QPointF oldPos;
  QImage* image;
  Thread* th;
  bool isOldPosNull;
  std::map<QString, QImage> userListImage;

  void drawPoint(const QPointF currentPos);
  void drawLine(const QPointF currentPos);
};
