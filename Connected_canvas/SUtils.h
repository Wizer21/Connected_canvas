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

private:
  static SUtils* instance;
  std::pair<int, int> resolution;
  int fontSize;
  SUtils();
};
