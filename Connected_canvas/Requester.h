#pragma once
#include "stdafx.h"
#include "ThreadRequest.h"

class Requester : public QObject
{
  Q_OBJECT

public:
  Requester();
  void logIn(QMainWindow* parent, QString pseudo, QString pass);

public slots:
  void sendLog(QString);

signals:
  void transfertLog(QString);
};
