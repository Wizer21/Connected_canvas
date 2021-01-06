#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Connected_canvas.h"

class Connected_canvas : public QMainWindow
{
  Q_OBJECT

public:
  Connected_canvas(QWidget* parent = Q_NULLPTR);

private:
  void build();
  Ui_Connected_canvasClass ui;
};
