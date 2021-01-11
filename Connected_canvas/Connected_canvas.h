#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Connected_canvas.h"
#include "SUtils.h"
#include "Requester.h"
#include "AccountLog.h"
#include "PenBuilder.h"
#include "Canvas.h"
#include "Friends.h"
#include "Rooms.h"

class Connected_canvas : public QMainWindow
{
  Q_OBJECT

public:
  Connected_canvas(QWidget* parent = Q_NULLPTR);

public slots:
  void setName(QString);
  void logInTriggered();
  void friendsTriggered();
  void roomsTriggered();
  void displayNewUser(QString);

protected:
  void closeEvent(QCloseEvent* event) override;

private:
  void build();
  void logIn();
  Ui_Connected_canvasClass ui;

  Requester* req;
  QLabel* labelPseudo;
  QPen* myPen;
};
