#pragma once
#include "stdafx.h"
#include "ThreadRequest.h"

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
  void newRequest();
  SUtils();
};
