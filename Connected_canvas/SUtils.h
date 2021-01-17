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
  void setIconOnButton(QPushButton* button, QString key, double ratioWidth, double ratioHeight);

private:
  SUtils();
  void loadPixmaps();
  QPixmap structPixmap(QString url, double widthRatio, double heightRatio);
  QImage structImage(QString url, double widthRatio, double heightRatio);

  int bSize;
  static SUtils* instance;
  std::pair<int, int> resolution;
  int fontSize;
  std::map<QString, QPixmap> pixmapList;
  std::map<QString, QImage> imageList;
};
