#include "Requester.h"

Requester::Requester()
{
}

void Requester::logIn(QMainWindow* parent, QString pseudo, QString pass)
{
  std::string url = "http://localhost:8080/connection/" + pseudo.toStdString() + "/" + pass.toStdString();
  ThreadRequest* thread = new ThreadRequest(url, parent);

  this->connect(thread, SIGNAL(resultRequest(QString)), this, SLOT(sendLog(QString)));
  this->connect(thread, &ThreadRequest::finished, thread, &QObject::deleteLater);
  thread->start();
}

void Requester::sendLog(QString name)
{
  emit transfertLog(name);
}