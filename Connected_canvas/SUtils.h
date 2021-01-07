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

private:
  static SUtils* instance;
  SUtils();
};
