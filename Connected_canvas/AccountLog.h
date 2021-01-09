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
  void newAccountClicked();
  void newAccountCreated(QString);
  void pageClicked();

signals:
  void transfertCurrentUser(QString);

private:
  QStackedWidget* widgetStack;
  QLineEdit* lineEditNewPseudo;
  QLineEdit* lineEditNewPassword;
  QLineEdit* lineEditNewPasswordbis;
  Requester* req;
};
