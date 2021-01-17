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
  QPushButton* buttonBrushType = new QPushButton(this);
  labelHoverColor = new QLabel(this);
  labelSelectedColor = new QLabel(this);
  ColorPicker* picker = new ColorPicker(this);

  QHBoxLayout* layoutParamPen = new QHBoxLayout(this);
  QLabel* labelPenSize = new QLabel(this);
  setPenSize = new QSpinBox(this);
  QLabel* labelPenOpacity = new QLabel(this);
  setPenOpacity = new QSpinBox(this);

  this->setLayout(mainLayout);
  mainLayout->addWidget(buttonBrushType, 0, 0);
  mainLayout->addWidget(labelHoverColor, 0, 1);
  mainLayout->addWidget(labelSelectedColor, 0, 2);
  mainLayout->addWidget(picker, 1, 0, 1, 3);
  mainLayout->addLayout(layoutParamPen, 2, 0, 1, 3);

  layoutParamPen->addWidget(labelPenSize);
  layoutParamPen->addWidget(setPenSize);
  layoutParamPen->addWidget(labelPenOpacity);
  layoutParamPen->addWidget(setPenOpacity);

  mainLayout->setColumnStretch(0, 1);
  mainLayout->setColumnStretch(1, 1);
  mainLayout->setColumnStretch(2, 2);
  mainLayout->setColumnStretch(3, 1);
  mainLayout->setSpacing(0);
  labelHoverColor->setContentsMargins(0, 0, 0, 0);
  labelSelectedColor->setContentsMargins(0, 0, 0, 0);

  setPenSize->setRange(0, 2000);
  setPenOpacity->setRange(0, 100);
  setPenSize->setValue(mainPen->width());
  setPenOpacity->setValue(100);
  buttonBrushType->setCursor(Qt::PointingHandCursor);

  auto utils = SUtils::getInstance();
  utils->setIconOnButton(buttonBrushType, "brush", 1, 1);
  labelPenSize->setPixmap(utils->getPixmap("penruler"));
  labelPenOpacity->setPixmap(utils->getPixmap("opacity"));
  setPenSize->setStyleSheet("border: 0px solid white;");
  setPenOpacity->setStyleSheet("border: 0px solid white;");

  connect(buttonBrushType, SIGNAL(clicked()), this, SLOT(drawClicked()));
  connect(setPenSize, SIGNAL(valueChanged(int)), this, SLOT(penSizeChanged(int)));
  connect(setPenOpacity, SIGNAL(valueChanged(int)), this, SLOT(penOpacityChanged(int)));
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
  color.setAlpha(round((alpha / 100.0) * 255.0));
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
  pix.fill(mainColor);
  labelSelectedColor->setPixmap(pix);
}

void PenBuilder::applyPickedLeaved()
{
  QPixmap pix(labelHoverColor->size());
  pix.fill(mainColor);
  labelHoverColor->setPixmap(pix);
}

void PenBuilder::setPenSizeFromWheel(int val)
{
  double penSize = mainPen->width();

  if (val > 0)
  {
    penSize = int(penSize * 1.1) + 1;
    if (penSize > 2000)
    {
      penSize = 2000;
    }
    mainPen->setWidth(penSize);
  }
  else
  {
    penSize = int(penSize * 0.9) - 1;
    if (penSize < 0)
    {
      penSize = 0;
    }
    mainPen->setWidth(penSize);
  }
  setPenSize->setValue(penSize);
}

void PenBuilder::penSizeChanged(int val)
{
  mainPen->setWidth(val);
  emit penSizeChanged();
}

void PenBuilder::penOpacityChanged(int val)
{
  alpha = val;
  mainColor.setAlpha(round((val / 100.0) * 255.0));
  mainPen->setColor(mainColor);
  setSelecter();
}

void PenBuilder::drawClicked()
{
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  if (*paint)
  {
    *paint = false;
    SUtils::getInstance()->setIconOnButton(button, "eraser", 1, 1);
  }
  else
  {
    *paint = true;
    SUtils::getInstance()->setIconOnButton(button, "brush", 1, 1);
  }
}