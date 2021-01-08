#pragma once
#include "stdafx.h"

class AccountLog : public QDialog
{
  Q_OBJECT

public:
  AccountLog();

public slots:
  void newAccountClicked();

private:
  QLineEdit* lineEditNewPseudo;
  QLineEdit* lineEditNewPassword;
  QLineEdit* lineEditNewPasswordbis;
};
