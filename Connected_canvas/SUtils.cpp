#include "SUtils.h"

SUtils::SUtils()
{
}

SUtils* SUtils::instance = 0;

void SUtils::pushResolution(std::pair<int, int> res, int newFontSize)
{
  resolution = res;
  fontSize = newFontSize;
  bSize = round(resolution.first / 45);
  loadPixmaps();
}

void SUtils::loadPixmaps()
{
  pixmapList.insert({"chroma", structPixmap(":/Connected_canvas/files/icons/IarsV.jpg", 6, 6)});
  pixmapList.insert({"show", structPixmap(":/Connected_canvas/files/icons/eyelight.png", 2, 2)});
  pixmapList.insert({"hide", structPixmap(":/Connected_canvas/files/icons/closeeyelight.png", 2, 2)});
  pixmapList.insert({"showOFF", structPixmap(":/Connected_canvas/files/icons/eyelightOFF.png", 2, 2)});
  pixmapList.insert({"hideOFF", structPixmap(":/Connected_canvas/files/icons/closeeyelightOFF.png", 2, 26)});
  pixmapList.insert({"brush", structPixmap(":/Connected_canvas/files/icons/brush.png", 2, 2)});
  pixmapList.insert({"eraser", structPixmap(":/Connected_canvas/files/icons/eraser.png", 2, 2)});
  pixmapList.insert({"opacity", structPixmap(":/Connected_canvas/files/icons/opacity.png", 0.5, 0.5)});
  pixmapList.insert({"penruler", structPixmap(":/Connected_canvas/files/icons/pencil-ruler.png", 0.5, 0.5)});

  imageList.insert({"chroma", structImage(":/Connected_canvas/files/icons/IarsV.jpg", 6, 6)});
}

QImage SUtils::structImage(QString url, double widthRatio, double heightRatio)
{
  return QImage(url).scaled(round(widthRatio * bSize), round(heightRatio * bSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QPixmap SUtils::structPixmap(QString url, double widthRatio, double heightRatio)
{
  return QPixmap(url).scaled(round(widthRatio * bSize), round(heightRatio * bSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QPixmap SUtils::getPixmap(QString key)
{
  return pixmapList.at(key);
}

QImage SUtils::getImage(QString key)
{
  return imageList.at(key);
}

void SUtils::setIconOnButton(QPushButton* button, QString key, double ratioWidth, double ratioHeight)
{
  button->setIcon(QIcon(pixmapList.at(key)));
  button->setIconSize(QSize(round(bSize * ratioWidth), round(bSize * ratioHeight)));
}

void SUtils::setFontOnWidget(QWidget* widget, double ratio)
{
  widget->setStyleSheet(QString("font-size: %1px;").arg(QString::number(round(fontSize * ratio))));
}

void SUtils::setFontAndColorOnWidget(QWidget* widget, QString color, double ratio)
{
  widget->setStyleSheet(QString("font-size: %1px; color: %2").arg(QString::number(round(fontSize * ratio)), color));
}