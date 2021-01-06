#include "Connected_canvas.h"
#include "stdafx.h"

Connected_canvas::Connected_canvas(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  build();
}

void Connected_canvas::build()
{
  QGridLayout* layoutMain = new QGridLayout(this);
  QLabel* labelPseudo = new QLabel("pseudo", this);

  QWidget* widgetDraw = new QWidget(this);
}