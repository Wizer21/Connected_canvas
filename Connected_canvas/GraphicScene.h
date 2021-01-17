#pragma once
#include "stdafx.h"
#include "Requester.h"
#include "LayerList.h"

class Thread : public QThread
{
  Q_OBJECT

public:
  Thread(QWidget* parent, QString roomName, QString userName, QImage* image, int& iterator, std::map<QString, QImage>& userListImage, LayerList* layerList);
  void stopClock();

public slots:
  void roomRequest(QString);
  void newIteration();

signals:
  void drawFromServer();

private:
  QString imageToB64(QImage image);
  QImage b64ToImage(char* base64Array);

  LayerList* layerList;
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
  GraphicScene(QWidget* parent, QPen* userPen, bool* isPainting, LayerList* layerList, QGraphicsView* view);
  void joinedRoom(QString roomName, QString userName);
  void closeThread();
  void drawCursor();

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
  Requester* req;
  LayerList* layerList;
  QStringList* sortedLayers;
  QString roomName;
  QString userName;
  QWidget* parent;
  QPen* userPen;
  bool* paint;
  bool online;
  QPointF oldPos;
  QImage* image;
  Thread* th;
  bool isOldPosNull;
  std::map<QString, QImage> userListImage;
  QGraphicsView* view;

  void drawPoint(const QPointF currentPos);
  void drawLine(const QPointF currentPos);
};
