#include "PenBuilder.h"

PenBuilder::PenBuilder(QWidget* parent, QPen* pen, bool* isPainting)
  : QWidget(parent)
{
  paint = isPainting;
  mainPen = pen;
  mainColor = (Qt::black);
  mainColor.setAlpha(255);
  alpha = 255;
  pen->setColor(mainColor);
  pen->setWidth(25);
  pen->setJoinStyle(Qt::RoundJoin);
  pen->setCapStyle(Qt::RoundCap);

  QGridLayout* mainLayout = new QGridLayout(this);
  QPushButton* buttonBrushType = new QPushButton("Draw", this);
  labelHoverColor = new QLabel(this);
  labelSelectedColor = new QLabel(this);
  ColorPicker* picker = new ColorPicker(this);
  QLabel* labelPenSize = new QLabel("Pen Size ", this);
  setPenSize = new QLineEdit(QString::number(mainPen->width()), this);
  QLabel* labelPenOpacity = new QLabel("Pen Opacity ", this);
  setPenOpacity = new QLineEdit("wip", this);

  this->setLayout(mainLayout);
  mainLayout->addWidget(buttonBrushType, 0, 0);
  mainLayout->addWidget(labelHoverColor, 0, 1);
  mainLayout->addWidget(labelSelectedColor, 0, 2);
  mainLayout->addWidget(picker, 1, 0, 2, 3);
  mainLayout->addWidget(labelPenSize, 3, 0, 1, 2);
  mainLayout->addWidget(setPenSize, 3, 2);
  mainLayout->addWidget(labelPenOpacity, 4, 0, 1, 2);
  mainLayout->addWidget(setPenOpacity, 4, 2);

  mainLayout->setColumnStretch(0, 1);
  mainLayout->setColumnStretch(1, 1);
  mainLayout->setColumnStretch(2, 2);
  mainLayout->setColumnStretch(3, 1);
  labelHoverColor->setContentsMargins(0, 0, 0, 0);
  labelSelectedColor->setContentsMargins(0, 0, 0, 0);
  setPenSize->setValidator(&QIntValidator());
  setPenOpacity->setValidator(&QIntValidator(0, 100));

  connect(buttonBrushType, SIGNAL(clicked()), this, SLOT(drawClicked()));
  connect(setPenSize, SIGNAL(textEdited(QString)), this, SLOT(penSizeChanged(QString)));
  connect(setPenOpacity, SIGNAL(textEdited(QString)), this, SLOT(penOpacityChanged(QString)));
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
  mainColor.setAlpha(round((alpha / 100.0) * 255.0));
  mainPen->setColor(mainColor);

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

void PenBuilder::penSizeChanged(QString str)
{
  mainPen->setWidth(str.toInt());
}

void PenBuilder::setPenSizeFromWheel(int val)
{
  double penSize = mainPen->width();

  if (val > 0)
  {
    penSize = int(penSize * 1.1) + 1;
    mainPen->setWidth(penSize);
  }
  else
  {
    penSize = int(penSize * 0.9) - 1;
    mainPen->setWidth(penSize);
  }
  setPenSize->setText(QString::number(penSize));
}

void PenBuilder::penOpacityChanged(QString str)
{
  alpha = str.toInt();
  mainColor.setAlpha(round((setPenOpacity->text().toDouble() / 100.0) * 255.0));
  mainPen->setColor(mainColor);
}

void PenBuilder::drawClicked()
{
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  if (*paint)
  {
    *paint = false;
    button->setText("Eraser");
  }
  else
  {
    *paint = true;
    button->setText("Draw");
  }
}