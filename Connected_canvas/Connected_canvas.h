#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Connected_canvas.h"
#include "SUtils.h"
#include "Requester.h"
#include "AccountLog.h"
#include "PenBuilder.h"
#include "Friends.h"
#include "Rooms.h"
#include "GraphicScene.h"
#include "LayerList.h"

class Connected_canvas : public QMainWindow
{
  Q_OBJECT

public:
  Connected_canvas(QWidget* parent = Q_NULLPTR);
  void updateUi();

public slots:
  void setName(QString);
  void logInTriggered();
  void friendsTriggered();
  void roomsTriggered();
  void displayNewUser(QString);
  void joinedRoom(QString);
  void newPenSize(int);
  void updateCursorOnPenSize();

protected:
  void closeEvent(QCloseEvent* event) override;

private:
  void build();
  Ui_Connected_canvasClass ui;

  GraphicScene* sceneMain;
  Requester* req;
  QLabel* labelPseudo;
  QLabel* labelRoomName;
  QPen* myPen;
  bool paint;
  PenBuilder* penBuilder;
  QString userName;
  QWidgetAction* actionFriends;
  QWidgetAction* actionRooms;
  QLabel* labelActionFriend;
  QLabel* labelActionRoom;
};
