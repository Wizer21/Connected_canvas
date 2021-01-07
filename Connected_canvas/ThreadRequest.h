#pragma once
#include "stdafx.h"

class ThreadRequest : public QThread
{
  Q_OBJECT

public:
  ThreadRequest(const std::string newUrl, QMainWindow* parent);
  ~ThreadRequest();

protected:
  void run() override;

signals:
  void resultRequest(const QString&);

private:
  std::string myUrl;
  void* curl;
  std::string download();
};
