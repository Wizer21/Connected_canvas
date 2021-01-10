#pragma once
#include "stdafx.h"

class PenBuilder : public QWidget
{
  Q_OBJECT

public:
  PenBuilder(QWidget* parent, QPen* pen);

private:
  QPen* mainPen;
};
