#include "PassWordDialog.h"

PassWordDialog::PassWordDialog(QWidget* parent, QString roomName, QString password)
  : QDialog(parent)
{
  this->setAttribute(Qt::WA_DeleteOnClose);
  pass = password;
  room = roomName;

  QGridLayout* layoutMain = new QGridLayout(this);
  QLabel* labelRoomName = new QLabel(roomName, this);
  QLabel* labelPassWord = new QLabel(tr("Password"), this);
  editPassword = new QLineEdit(this);
  QPushButton* buttonValidate = new QPushButton(tr("Validate"), this);

  this->setLayout(layoutMain);
  layoutMain->addWidget(labelRoomName);
  layoutMain->addWidget(labelPassWord);
  layoutMain->addWidget(editPassword);
  layoutMain->addWidget(buttonValidate);

  editPassword->setEchoMode(QLineEdit::Password);

  connect(buttonValidate, SIGNAL(clicked()), this, SLOT(validButtonClicked()));
}

void PassWordDialog::validButtonClicked()
{
  if (editPassword->text() == pass)
  {
    emit roomPasswordSucces(room);
    this->close();
  }
}