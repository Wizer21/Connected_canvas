#include "PenBuilder.h"

PenBuilder::PenBuilder(QWidget* parent, QPen* pen)
  : QWidget(parent)
{
  mainPen = pen;
  mainColor = (Qt::black);
  pen->setColor(mainColor);
  pen->setWidth(25);
  pen->setJoinStyle(Qt::RoundJoin);

  QGridLayout* mainLayout = new QGridLayout(this);
  QPushButton* buttonBrushType = new QPushButton("contain brush", this);
  labelHoverColor = new QLabel(this);
  labelSelectedColor = new QLabel(this);
  ColorPicker* picker = new ColorPicker(this);

  this->setLayout(mainLayout);
  mainLayout->addWidget(buttonBrushType, 0, 0);
  mainLayout->addWidget(labelHoverColor, 0, 1);
  mainLayout->addWidget(labelSelectedColor, 0, 2);
  mainLayout->addWidget(picker, 1, 0, 2, 3);

  mainLayout->setColumnStretch(0, 1);
  mainLayout->setColumnStretch(1, 1);
  mainLayout->setColumnStretch(2, 2);
  labelHoverColor->setContentsMargins(0, 0, 0, 0);
  labelSelectedColor->setContentsMargins(0, 0, 0, 0);

  setSelecter();

  connect(picker, SIGNAL(displayHoverColor(QColor)), this, SLOT(applyHoverColor(QColor)));
  connect(picker, SIGNAL(displaySelectedColor(QColor)), this, SLOT(applySelectedColor(QColor)));
  connect(picker, SIGNAL(pickerLeaved()), this, SLOT(applyPickedLeaved()));
}

void PenBuilder::setSelecter()
{
  QPixmap pix(labelHoverColor->size());
  pix.fill(mainColor);
  labelHoverColor->setPixmap(pix);
  QPixmap pix1(labelSelectedColor->size());
  pix1.fill(mainColor);
  labelSelectedColor->setPixmap(pix1);
}

void PenBuilder::applyHoverColor(QColor color)
{
  QPixmap pix(labelHoverColor->size());
  pix.fill(color);
  labelHoverColor->setPixmap(pix);
}

void PenBuilder::applySelectedColor(QColor color)
{
  mainColor = color;
  mainPen->setColor(color);

  QPixmap pix(labelSelectedColor->size());
  pix.fill(color);
  labelSelectedColor->setPixmap(pix);
}

void PenBuilder::applyPickedLeaved()
{
  QPixmap pix(labelHoverColor->size());
  pix.fill(mainColor);
  labelHoverColor->setPixmap(pix);
}