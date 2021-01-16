#include "SUtils.h"

SUtils::SUtils()
{
}

SUtils* SUtils::instance = 0;

void SUtils::pushResolution(std::pair<int, int> res, int newFontSize)
{
  resolution = res;
  fontSize = newFontSize;
  loadPixmaps();
}

void SUtils::loadPixmaps()
{
  int bSize = round(resolution.first / 45);
  pixmapList.insert({"chroma", structPixmap(":/Connected_canvas/files/icons/IarsV.jpg", 4, 4, bSize)});

  imageList.insert({"chroma", structImage(":/Connected_canvas/files/icons/IarsV.jpg", 4, 4, bSize)});
}

QImage SUtils::structImage(QString url, int widthRatio, int heightRatio, int baseSize)
{
  return QImage(url).scaled(round(widthRatio * baseSize), round(heightRatio * baseSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QPixmap SUtils::structPixmap(QString url, int widthRatio, int heightRatio, int baseSize)
{
  return QPixmap(url).scaled(round(widthRatio * baseSize), round(heightRatio * baseSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QPixmap SUtils::getPixmap(QString key)
{
  return pixmapList.at(key);
}

QImage SUtils::getImage(QString key)
{
  return imageList.at(key);
}

void SUtils::setFontOnWidget(QWidget* widget, double ratio)
{
  widget->setStyleSheet(QString("font-size: %1px;").arg(QString::number(round(fontSize * ratio))));
}