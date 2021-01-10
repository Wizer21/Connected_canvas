#include "Friends.h"

Friends::Friends(QWidget* parent, QString new_userName)
  : QDialog(parent)
{
  userName = new_userName;
  build();
  loadFriends();
  this->resize(500, 500);
}

void Friends::build()
{
  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  QScrollArea* area = new QScrollArea(this);
  QWidget* widgetArea = new QWidget(this);
  layoutArea = new QVBoxLayout(this);

  this->setLayout(mainLayout);
  mainLayout->addWidget(area);
  area->setWidget(widgetArea);
  widgetArea->setLayout(layoutArea);

  layoutArea->setAlignment(Qt::AlignTop);
  area->setWidgetResizable(true);

  req = new Requester();
}

void Friends::loadFriends()
{
  if (userName != "Offline")
  {
    QLabel* lab = new QLabel(tr("Friends List"), this);
    layoutArea->addWidget(lab);
    connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(setFriendsList(QString)));
    req->frienList(this, userName);
  }
  else
  {
    QLabel* lab = new QLabel(tr("OFFLINE"), this);
    layoutArea->addWidget(lab);
    loadOnlineUsers();
  }
}

void Friends::setFriendsList(QString request)
{
  disconnect(req, SIGNAL(transfertRequest(QString)), nullptr, nullptr);
  QStringList friends(request.split(","));
  for (const QString& name : friends)
  {
    QLabel* user = new QLabel(name, this);
    layoutArea->addWidget(user);
  }
  loadOnlineUsers();
}

void Friends::loadOnlineUsers()
{
  QLabel* lab = new QLabel(tr("Online Users"), this);
  layoutArea->addWidget(lab);

  connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(setOnlineList(QString)));
  req->onlineUsers(this);
}

void Friends::setOnlineList(QString request)
{
  QStringList usersList(request.split(","));
  for (const QString& name : usersList)
  {
    QLabel* user = new QLabel(name, this);
    layoutArea->addWidget(user);
  }
}