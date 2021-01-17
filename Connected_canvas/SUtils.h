#pragma once
#include "stdafx.h"

class SUtils
{
public:
  static SUtils* getInstance()
  {
    if (!instance)
      instance = new SUtils;
    return instance;
  }
  void pushResolution(std::pair<int, int> res, int newFontSize);
  void setFontOnWidget(QWidget* widget, double ratio);
  void setFontAndColorOnWidget(QWidget* widget, QString color, double ratio);
  QPixmap getPixmap(QString key);
  QImage getImage(QString key);

private:
  SUtils();
  void loadPixmaps();
  QPixmap structPixmap(QString url, int widthRatio, int heightRatio, int baseSize);
  QImage structImage(QString url, int widthRatio, int heightRatio, int baseSize);

  static SUtils* instance;
  std::pair<int, int> resolution;
  int fontSize;
  std::map<QString, QPixmap> pixmapList;
  std::map<QString, QImage> imageList;
};
