#pragma once
#include "stdafx.h"
#include "Requester.h"

class Rooms : public QDialog
{
  Q_OBJECT

public:
  Rooms(QWidget* parent);

public slots:
  void newRoomClicked();

private:
  void build();
  void loadRooms();
  Requester* req;
};
