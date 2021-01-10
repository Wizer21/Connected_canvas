#pragma once
#include <qdialog.h>
#include "SUtils.h"
#include "Requester.h"

class Friends : public QDialog
{
  Q_OBJECT

public:
  Friends(QWidget* parent, QString new_userName);

public slots:
  void setFriendsList(QString request);
  void setOnlineList(QString request);

private:
  void build();
  void loadFriends();
  void loadOnlineUsers();

  QString userName;
  QVBoxLayout* layoutArea;
  Requester* req;
};
