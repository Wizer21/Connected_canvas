#pragma once
#include "stdafx.h"

class ThreadRequest : public QThread
{
  Q_OBJECT

public:
  ThreadRequest(const std::string newUrl, QWidget* parent, std::string post = "");
  ~ThreadRequest();

protected:
  void run() override;

signals:
  void resultRequest(const QString&);

private:
  std::string myUrl;
  std::string myPost;
  void* curl;
  std::string download();
};
