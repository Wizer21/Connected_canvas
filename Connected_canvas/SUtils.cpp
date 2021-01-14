#include "SUtils.h"

SUtils::SUtils()
{
}

SUtils* SUtils::instance = 0;

void SUtils::pushResolution(std::pair<int, int> res, int newFontSize)
{
  resolution = res;
  fontSize = newFontSize;
}

void SUtils::setFontOnWidget(QWidget* widget, double ratio)
{
  widget->setStyleSheet(QString("font-size: %1px;").arg(QString::number(round(fontSize * ratio))));
}