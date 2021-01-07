#include "Requester.h"

Requester::Requester()
{
}

void Requester::callRequest(QMainWindow* parent)
{
  std::string url{"http://localhost:8080/pseudo"};
  ThreadRequest* thread = new ThreadRequest(url, parent);

  this->connect(thread, SIGNAL(resultRequest(QString)), this, SLOT(sendName(QString)));
  this->connect(thread, &ThreadRequest::finished, thread, &QObject::deleteLater);
  thread->start();
}

void Requester::sendName(QString name)
{
  emit transfertName(name);
}