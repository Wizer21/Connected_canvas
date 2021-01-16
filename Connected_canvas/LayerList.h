#pragma once
#include "stdafx.h"

class LayerList : public QScrollArea
{
  Q_OBJECT

public:
  LayerList(QWidget* parent);
  void clearList();
  void newUser(QString userName);
  void leavedUser(QString userName);
  void reBuild();

public slots:
  void userUp();
  void userDown();
  void toggleVisible();

private:
  void updateDisplayedList();

  QVBoxLayout* mainLayout;
  QStringList displayedUsers;
  QVector<std::pair<QString, bool>> userPosition;
  std::vector<QWidget*> widgetList;
};
