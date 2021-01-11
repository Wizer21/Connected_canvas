#pragma once
#include "stdafx.h"
#include "Requester.h"
#include "NewRoomDialog.h"

class Rooms : public QDialog
{
  Q_OBJECT

public:
  Rooms(QWidget* parent);

public slots:
  void newRoomClicked();
  void setCurrentRoom(QString);

private:
  void build();
  void loadRooms();
  Requester* req;
  QLabel* currentRoom;
};
