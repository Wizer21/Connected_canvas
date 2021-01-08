#include "AccountLog.h"

AccountLog::AccountLog()
{

  QGridLayout* layoutMain = new QGridLayout(this);
  QVBoxLayout* layoutButtons = new QVBoxLayout(this);
  QPushButton* buttonLog = new QPushButton(tr("Login"), this);
  QPushButton* buttonNewAccount = new QPushButton(tr("New Account"), this);
  QStackedWidget* widgetStack = new QStackedWidget(this);

  QWidget* widgetLogTitle = new QWidget(this);
  QVBoxLayout* layoutLog = new QVBoxLayout(this);
  QLabel* labelLogTitle = new QLabel(tr("Login"), this);
  QLabel* labelLogPseudo = new QLabel(tr("Pseudo"), this);
  QLineEdit* lineEditLogPseudo = new QLineEdit(this);
  QLabel* labelLogPassword = new QLabel(tr("Password"), this);
  QLineEdit* lineEditLogPassword = new QLineEdit(this);
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
  layoutLog->addWidget(lineEditLogPseudo);
  layoutLog->addWidget(labelLogPassword);
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

  connect(buttonNewValidate, SIGNAL(clicked()), this, SLOT(newAccountClicked()));

  this->show();
}

void AccountLog::newAccountClicked()
{
  QString name = lineEditNewPseudo->text();
  QString pass = lineEditNewPassword->text();
  QString passBis = lineEditNewPasswordbis->text();

  if (name.isEmpty() || pass.isEmpty() || name.isEmpty())
  {
  }
}