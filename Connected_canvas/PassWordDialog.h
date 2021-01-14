#pragma once
#include <qdialog.h>
#include "stdafx.h"

class PassWordDialog : public QDialog
{
  Q_OBJECT

public:
  PassWordDialog(QWidget* parent, QString roomName, QString password);

public slots:
  void validButtonClicked();

signals:
  void roomPasswordSucces(QString);

private:
  QString pass;
  QString room;
  QLineEdit* editPassword;
};
