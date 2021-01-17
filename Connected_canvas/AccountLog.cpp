#include "AccountLog.h"

AccountLog::AccountLog()
{
  showLog = false;
  showCreate = false;

  QGridLayout* layoutMain = new QGridLayout(this);
  QVBoxLayout* layoutButtons = new QVBoxLayout(this);
  QPushButton* buttonLog = new QPushButton(tr("Login"), this);
  QPushButton* buttonNewAccount = new QPushButton(tr("New Account"), this);
  widgetStack = new QStackedWidget(this);

  QWidget* widgetLogTitle = new QWidget(this);
  QGridLayout* layoutLog = new QGridLayout(this);
  QLabel* labelLogTitle = new QLabel(tr("Login"), this);
  QLabel* labelLogPseudo = new QLabel(tr("Nickname"), this);
  lineEditLogPseudo = new QLineEdit(this);
  QLabel* labelLogPassword = new QLabel(tr("Password"), this);
  lineEditLogPassword = new QLineEdit(this);
  buttonPassLogIn = new QPushButton(this);
  labelErrorLog = new QLabel(this);
  QPushButton* buttonLogValidate = new QPushButton(tr("Validate"), this);

  QWidget* widgetNewTitle = new QWidget(this);
  QGridLayout* layoutNew = new QGridLayout(this);
  QLabel* labelNewTitle = new QLabel(tr("New Account"), this);
  QLabel* labelNewPseudo = new QLabel(tr("Nickname"), this);
  lineEditNewPseudo = new QLineEdit(this);
  QLabel* labelNewPassword = new QLabel(tr("Password"), this);
  lineEditNewPassword = new QLineEdit(this);
  buttonEyeLogPass = new QPushButton(this);
  QLabel* labelNewPasswordbis = new QLabel(tr("Confirm Password"), this);
  lineEditNewPasswordbis = new QLineEdit(this);
  buttonEyeLogValid = new QPushButton(this);
  labelErrorCreate = new QLabel(this);
  QPushButton* buttonNewValidate = new QPushButton(tr("Validate"), this);

  this->setLayout(layoutMain);
  layoutMain->addLayout(layoutButtons, 0, 0);
  layoutButtons->addWidget(buttonLog);
  layoutButtons->addWidget(buttonNewAccount);
  layoutMain->addWidget(widgetStack, 0, 1);

  widgetLogTitle->setLayout(layoutLog);
  layoutLog->addWidget(labelLogTitle, 0, 0, 1, 2);
  layoutLog->addWidget(labelLogPseudo, 1, 0, 1, 2);
  layoutLog->addWidget(lineEditLogPseudo, 2, 0, 1, 2);
  layoutLog->addWidget(labelLogPassword, 3, 0, 1, 2);
  layoutLog->addWidget(lineEditLogPassword, 4, 0);
  layoutLog->addWidget(buttonPassLogIn, 4, 1);
  layoutLog->addWidget(labelErrorLog, 5, 0, 1, 2);
  layoutLog->addWidget(buttonLogValidate, 6, 0, 1, 2);

  widgetNewTitle->setLayout(layoutNew);
  layoutNew->addWidget(labelNewTitle, 0, 0, 1, 2);
  layoutNew->addWidget(labelNewPseudo, 1, 0, 1, 2);
  layoutNew->addWidget(lineEditNewPseudo, 2, 0, 1, 2);
  layoutNew->addWidget(labelNewPassword, 3, 0, 1, 2);
  layoutNew->addWidget(lineEditNewPassword, 4, 0);
  layoutNew->addWidget(buttonEyeLogPass, 4, 1);
  layoutNew->addWidget(labelNewPasswordbis, 5, 0, 1, 2);
  layoutNew->addWidget(lineEditNewPasswordbis, 6, 0);
  layoutNew->addWidget(buttonEyeLogValid, 6, 1);
  layoutNew->addWidget(labelErrorCreate, 7, 0, 1, 2);
  layoutNew->addWidget(buttonNewValidate, 8, 0, 1, 2);

  widgetStack->addWidget(widgetLogTitle);
  widgetStack->addWidget(widgetNewTitle);

  widgetStack->setCurrentIndex(0);
  buttonLog->setObjectName("0");
  buttonNewAccount->setObjectName("1");
  layoutButtons->setAlignment(Qt::AlignTop);
  layoutLog->setAlignment(Qt::AlignTop);
  layoutNew->setAlignment(Qt::AlignTop);

  SUtils::getInstance()->setFontOnWidget(labelLogTitle, 1.5);
  SUtils::getInstance()->setFontOnWidget(labelNewTitle, 1.5);

  lineEditLogPassword->setEchoMode(QLineEdit::Password);
  lineEditNewPassword->setEchoMode(QLineEdit::Password);
  lineEditNewPasswordbis->setEchoMode(QLineEdit::Password);
  buttonPassLogIn->setIcon(QIcon(SUtils::getInstance()->getPixmap("hide")));
  buttonEyeLogPass->setIcon(QIcon(SUtils::getInstance()->getPixmap("hide")));
  buttonEyeLogValid->setIcon(QIcon(SUtils::getInstance()->getPixmap("hide")));
  buttonPassLogIn->setObjectName("0");
  SUtils::getInstance()->setFontAndColorOnWidget(labelErrorLog, "#f44336", 0.5);
  SUtils::getInstance()->setFontAndColorOnWidget(labelErrorCreate, "#f44336", 0.5);

  connect(buttonPassLogIn, SIGNAL(clicked()), this, SLOT(toggleEcho()));
  connect(buttonEyeLogPass, SIGNAL(clicked()), this, SLOT(toggleEcho()));
  connect(buttonEyeLogValid, SIGNAL(clicked()), this, SLOT(toggleEcho()));

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

  if (name.isEmpty())
  {
    labelErrorCreate->setText(tr("Nickname not referenced"));
    return;
  }
  if (pass.isEmpty())
  {
    labelErrorCreate->setText(tr("Password not referenced"));
    return;
  }
  if (passBis.isEmpty())
  {
    labelErrorCreate->setText(tr("Validator not referenced"));
    return;
  }
  if (pass != passBis)
  {
    labelErrorCreate->setText(tr("Password not matching"));
    return;
  }

  connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(newAccountCreated(QString)));
  req->creatAccount(this, name, pass);
}

void AccountLog::loginClicked()
{
  QString name = lineEditLogPseudo->text();
  QString pass = lineEditLogPassword->text();

  if (name.isEmpty())
  {
    labelErrorLog->setText(tr("Nickname not referenced"));
    return;
  }
  if (pass.isEmpty())
  {
    labelErrorLog->setText(tr("Password not referenced"));
    return;
  }

  connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(logInRequest(QString)));
  req->logIn(this, name, pass);
}

void AccountLog::newAccountCreated(QString request)
{
  request.replace("\n", "");
  if (request == "Nickname not avaible")
  {
    labelErrorCreate->setText(tr("Nickname not avaible"));
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
    labelErrorLog->setText(tr("Wrong nickname or password"));
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

void AccountLog::toggleEcho()
{
  if (sender()->objectName() == "0")
  {
    if (showLog)
    {
      showLog = false;
      buttonPassLogIn->setIcon(SUtils::getInstance()->getPixmap("hide"));
      lineEditLogPassword->setEchoMode(QLineEdit::Password);
    }
    else
    {
      showLog = true;
      buttonPassLogIn->setIcon(SUtils::getInstance()->getPixmap("show"));
      lineEditLogPassword->setEchoMode(QLineEdit::Normal);
    }
  }
  else
  {
    if (showCreate)
    {
      showCreate = false;
      buttonEyeLogPass->setIcon(SUtils::getInstance()->getPixmap("hide"));
      buttonEyeLogValid->setIcon(SUtils::getInstance()->getPixmap("hide"));
      lineEditNewPassword->setEchoMode(QLineEdit::Password);
      lineEditNewPasswordbis->setEchoMode(QLineEdit::Password);
    }
    else
    {
      showCreate = true;
      buttonEyeLogPass->setIcon(SUtils::getInstance()->getPixmap("show"));
      buttonEyeLogValid->setIcon(SUtils::getInstance()->getPixmap("show"));
      lineEditNewPassword->setEchoMode(QLineEdit::Normal);
      lineEditNewPasswordbis->setEchoMode(QLineEdit::Normal);
    }
  }
}