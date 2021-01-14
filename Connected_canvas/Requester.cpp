#include "Requester.h"

Requester::Requester()
{
}

void Requester::creatAccount(QWidget* parent, QString pseudo, QString pass)
{
  std::string url = "http://localhost:8080/create?pseudo=" + pseudo.toStdString() + "&" + "pass=" + pass.toStdString();
  ThreadRequest* thread = new ThreadRequest(url, parent);

  this->connect(thread, SIGNAL(resultRequest(QString)), this, SLOT(sendLog(QString)));
  this->connect(thread, &ThreadRequest::finished, thread, &QObject::deleteLater);
  thread->start();
}

void Requester::logIn(QWidget* parent, QString pseudo, QString pass)
{
  std::string url = "http://localhost:8080/login?pseudo=" + pseudo.toStdString() + "&" + "pass=" + pass.toStdString();
  ThreadRequest* thread = new ThreadRequest(url, parent);

  this->connect(thread, SIGNAL(resultRequest(QString)), this, SLOT(sendLog(QString)));
  this->connect(thread, &ThreadRequest::finished, thread, &QObject::deleteLater);
  thread->start();
}

void Requester::logOut(QWidget* parent, QString pseudo)
{
  std::string url = "http://localhost:8080/logout?pseudo=" + pseudo.toStdString();
  ThreadRequest* thread = new ThreadRequest(url, parent);

  this->connect(thread, &ThreadRequest::finished, thread, &QObject::deleteLater);
  thread->start();
  thread->wait();
}

void Requester::frienList(QWidget* parent, QString pseudo)
{
  std::string url = "http://localhost:8080/friendlist?pseudo=" + pseudo.toStdString();
  ThreadRequest* thread = new ThreadRequest(url, parent);

  this->connect(thread, SIGNAL(resultRequest(QString)), this, SLOT(sendLog(QString)));
  this->connect(thread, &ThreadRequest::finished, thread, &QObject::deleteLater);
  thread->start();
}

void Requester::onlineUsers(QWidget* parent)
{
  std::string url = "http://localhost:8080/onlineusers";
  ThreadRequest* thread = new ThreadRequest(url, parent);

  this->connect(thread, SIGNAL(resultRequest(QString)), this, SLOT(sendLog(QString)));
  this->connect(thread, &ThreadRequest::finished, thread, &QObject::deleteLater);
  thread->start();
}

void Requester::createRoom(QWidget* parent, QString name, QString password)
{
  std::string url = "http://localhost:8080/createroom?name=" + name.toStdString() + "&pass=" + password.toStdString();
  ThreadRequest* thread = new ThreadRequest(url, parent);

  this->connect(thread, SIGNAL(resultRequest(QString)), this, SLOT(sendLog(QString)));
  this->connect(thread, &ThreadRequest::finished, thread, &QObject::deleteLater);
  thread->start();
}

void Requester::updateRoom(QWidget* parent, QString roomName, QString userName, QString base64, int iterator)
{
  std::string url = "http://localhost:8080/updateroom?room=" + roomName.toStdString() + "&user=" + userName.toStdString() + "&it=" + QString::number(iterator).toStdString();
  ThreadRequest* thread = new ThreadRequest(url, parent, base64.toStdString());

  this->connect(thread, SIGNAL(resultRequest(QString)), this, SLOT(sendLog(QString)));
  this->connect(thread, &ThreadRequest::finished, thread, &QObject::deleteLater);
  thread->start();
}

void Requester::roomListPassword(QWidget* parent)
{
  std::string url = "http://localhost:8080/roomlistpass";
  ThreadRequest* thread = new ThreadRequest(url, parent);

  this->connect(thread, SIGNAL(resultRequest(QString)), this, SLOT(sendLog(QString)));
  this->connect(thread, &ThreadRequest::finished, thread, &QObject::deleteLater);
  thread->start();
}

void Requester::sendLog(QString name)
{
  emit transfertRequest(name);
}