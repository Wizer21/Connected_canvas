#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Connected_canvas.h"
#include "SUtils.h"
#include "Requester.h"

class Connected_canvas : public QMainWindow
{
  Q_OBJECT

public:
  Connected_canvas(QWidget* parent = Q_NULLPTR);

public slots:
  void setName(QString);

private:
  void build();
  void loadData();
  Ui_Connected_canvasClass ui;

  Requester* req;
  QLabel* labelPseudo;
};
