#pragma once
#include "stdafx.h"
#include "Requester.h"
#include "SUtils.h"

class NewRoomDialog : public QDialog
{
  Q_OBJECT

public:
  NewRoomDialog(QWidget* parent);

public slots:
  void setIsRoomPublic(int);
  void validButtonClicked();
  void applyRequest(QString);
  void toggleShow();

signals:
  void newCurrentRoom(QString);

private:
  void build();
  QLineEdit* lineeditName;
  QCheckBox* checkPublicRoom;
  QLabel* labelPassword;
  QLineEdit* lineeditPassword;
  Requester* req;
  QPushButton* buttonShow;
  bool showPass;
};
