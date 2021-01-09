#pragma once
#include "stdafx.h"
#include "Requester.h"
#include "SUtils.h"

class AccountLog : public QDialog
{
  Q_OBJECT

public:
  AccountLog();

public slots:
  void loginClicked();
  void newAccountClicked();
  void newAccountCreated(QString);
  void logInRequest(QString);
  void pageClicked();

signals:
  void transfertCurrentUser(QString);

private:
  Requester* req;
  QStackedWidget* widgetStack;

  QLineEdit* lineEditLogPseudo;
  QLineEdit* lineEditLogPassword;

  QLineEdit* lineEditNewPseudo;
  QLineEdit* lineEditNewPassword;
  QLineEdit* lineEditNewPasswordbis;
};
