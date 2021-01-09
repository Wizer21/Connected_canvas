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
}

void Requester::sendLog(QString name)
{
  emit transfertRequest(name);
}