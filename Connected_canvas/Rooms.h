#pragma once
#include "stdafx.h"
#include "Requester.h"
#include "NewRoomDialog.h"
#include "PassWordDialog.h"

class Rooms : public QDialog
{
  Q_OBJECT

public:
  Rooms(QWidget* parent);

public slots:
  void newRoomClicked();
  void setCurrentRoom(QString);
  void setRoomList(QString);
  void joinRoomClicked();

signals:
  void sendNewRoom(QString);

private:
  void build();
  Requester* req;
  QLabel* currentRoom;
  QVBoxLayout* layoutArea;
  std::map<QString, QString> passwordList;
};
