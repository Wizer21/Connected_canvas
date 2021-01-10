#include "AccountLog.h"

AccountLog::AccountLog()
{
  QGridLayout* layoutMain = new QGridLayout(this);
  QVBoxLayout* layoutButtons = new QVBoxLayout(this);
  QPushButton* buttonLog = new QPushButton(tr("Login"), this);
  QPushButton* buttonNewAccount = new QPushButton(tr("New Account"), this);
  widgetStack = new QStackedWidget(this);

  QWidget* widgetLogTitle = new QWidget(this);
  QVBoxLayout* layoutLog = new QVBoxLayout(this);
  QLabel* labelLogTitle = new QLabel(tr("Login"), this);
  QLabel* labelLogPseudo = new QLabel(tr("Pseudo"), this);
  lineEditLogPseudo = new QLineEdit(this);
  QLabel* labelLogPassword = new QLabel(tr("Password"), this);
  lineEditLogPassword = new QLineEdit(this);
  QPushButton* buttonLogValidate = new QPushButton(tr("Validate"), this);

  QWidget* widgetNewTitle = new QWidget(this);
  QVBoxLayout* layoutNew = new QVBoxLayout(this);
  QLabel* labelNewTitle = new QLabel(tr("New Account"), this);
  QLabel* labelNewPseudo = new QLabel(tr("Pseudo"), this);
  lineEditNewPseudo = new QLineEdit(this);
  QLabel* labelNewPassword = new QLabel(tr("Password"), this);
  lineEditNewPassword = new QLineEdit(this);
  QLabel* labelNewPasswordbis = new QLabel(tr("Confirm Password"), this);
  lineEditNewPasswordbis = new QLineEdit(this);
  QPushButton* buttonNewValidate = new QPushButton(tr("Validate"), this);

  this->setLayout(layoutMain);
  layoutMain->addLayout(layoutButtons, 0, 0);
  layoutButtons->addWidget(buttonLog);
  layoutButtons->addWidget(buttonNewAccount);
  layoutMain->addWidget(widgetStack, 0, 1);

  widgetLogTitle->setLayout(layoutLog);
  layoutLog->addWidget(labelLogTitle);
  layoutLog->addWidget(labelLogPseudo);
  layoutLog->addWidget(lineEditLogPseudo);
  layoutLog->addWidget(labelLogPassword);
  layoutLog->addWidget(lineEditLogPassword);
  layoutLog->addWidget(buttonLogValidate);

  widgetNewTitle->setLayout(layoutNew);
  layoutNew->addWidget(labelNewTitle);
  layoutNew->addWidget(labelNewPseudo);
  layoutNew->addWidget(lineEditNewPseudo);
  layoutNew->addWidget(labelNewPassword);
  layoutNew->addWidget(lineEditNewPassword);
  layoutNew->addWidget(labelNewPasswordbis);
  layoutNew->addWidget(lineEditNewPasswordbis);
  layoutNew->addWidget(buttonNewValidate);

  widgetStack->addWidget(widgetLogTitle);
  widgetStack->addWidget(widgetNewTitle);

  widgetStack->setCurrentIndex(0);
  buttonLog->setObjectName("0");
  buttonNewAccount->setObjectName("1");
  layoutButtons->setAlignment(Qt::AlignTop);
  layoutLog->setAlignment(Qt::AlignTop);
  layoutNew->setAlignment(Qt::AlignTop);

  req = new Requester();
  connect(buttonLogValidate, SIGNAL(clicked()), this, SLOT(loginClicked()));
  connect(buttonNewValidate, SIGNAL(clicked()), this, SLOT(newAccountClicked()));
  connect(buttonLog, SIGNAL(clicked()), this, SLOT(pageClicked()));
  connect(buttonNewAccount, SIGNAL(clicked()), this, SLOT(pageClicked()));
}

void AccountLog::newAccountClicked()
{
  QString name = lineEditNewPseudo->text();
  QString pass = lineEditNewPassword->text();
  QString passBis = lineEditNewPasswordbis->text();

  if (name.isEmpty() || pass.isEmpty() || passBis.isEmpty() || pass != passBis)
  {
    return;
  }

  connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(newAccountCreated(QString)));
  req->creatAccount(this, name, pass);
}

void AccountLog::loginClicked()
{
  QString name = lineEditLogPseudo->text();
  QString pass = lineEditLogPassword->text();

  if (name.isEmpty() || pass.isEmpty())
  {
    return;
  }

  connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(logInRequest(QString)));
  req->logIn(this, name, pass);
}

void AccountLog::newAccountCreated(QString request)
{
  request.replace("\n", "");
  if (request != "done")
  {
    return;
  }
  emit transfertCurrentUser(lineEditNewPseudo->text());
  this->close();
}

void AccountLog::logInRequest(QString request)
{
  request.replace("\n", "");
  if (request == "false")
  {
    return;
  }
  emit transfertCurrentUser(lineEditLogPseudo->text());
  this->close();
}

void AccountLog::pageClicked()
{
  QString id = sender()->objectName();
  if (id == "0")
  {
    widgetStack->setCurrentIndex(0);
  }
  else
  {
    widgetStack->setCurrentIndex(1);
  }
}