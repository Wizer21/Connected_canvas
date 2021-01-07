#pragma once
#include "stdafx.h"
#include "ThreadRequest.h"

class Requester : public QObject
{
  Q_OBJECT

public:
  Requester();
  void callRequest(QMainWindow* parent);

public slots:
  void sendName(QString);

signals:
  void transfertName(QString);
};
