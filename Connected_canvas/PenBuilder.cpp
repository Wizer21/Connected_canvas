#include "PenBuilder.h"

PenBuilder::PenBuilder(QWidget* parent, QPen* pen)
  : QWidget(parent)
{
  mainPen = pen;
  pen->setColor(Qt::red);
  pen->setWidth(25);
  pen->setJoinStyle(Qt::RoundJoin);

  QGridLayout* mainLayout = new QGridLayout(this);
  QPushButton* buttonBrushType = new QPushButton("contain brush", this);
  QLabel* labelColor = new QLabel("color", this);

  this->setLayout(mainLayout);
  mainLayout->addWidget(buttonBrushType, 0, 0);
  mainLayout->addWidget(labelColor, 0, 1);
}
