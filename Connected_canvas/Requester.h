#pragma once
#include "stdafx.h"
#include "ThreadRequest.h"

class Requester : public QObject
{
  Q_OBJECT

public:
  Requester();
  void creatAccount(QWidget* parent, QString pseudo, QString pass);
  void logIn(QWidget* parent, QString pseudo, QString pass);
  void logOut(QWidget* parent, QString pseudo);
  void frienList(QWidget* parent, QString pseudo);
  void onlineUsers(QWidget* parent);
  void createRoom(QWidget* parent, QString name, bool isLock, QString password);

public slots:
  void sendLog(QString);

signals:
  void transfertRequest(QString);
};
