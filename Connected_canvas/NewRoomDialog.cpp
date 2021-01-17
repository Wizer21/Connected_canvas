#include "NewRoomDialog.h"

NewRoomDialog::NewRoomDialog(QWidget* parent)
  : QDialog(parent)
{
  showPass = false;
  build();
  this->setAttribute(Qt::WA_DeleteOnClose);
  this->resize(400, 300);
}

void NewRoomDialog::build()
{
  QGridLayout* layoutMain = new QGridLayout(this);
  QLabel* labelTitle = new QLabel(tr("New Room"), this);
  QLabel* labelRoomName = new QLabel(tr("Room name"), this);
  lineeditName = new QLineEdit(this);
  checkPublicRoom = new QCheckBox(tr("Private room"), this);
  labelPassword = new QLabel(tr("Room password"), this);
  lineeditPassword = new QLineEdit(this);
  buttonShow = new QPushButton(this);
  QPushButton* buttonValidate = new QPushButton(tr("Validate"), this);

  req = new Requester();

  this->setLayout(layoutMain);
  layoutMain->addWidget(labelTitle, 0, 0, 1, 2);
  layoutMain->addWidget(labelRoomName, 1, 0, 1, 2);
  layoutMain->addWidget(lineeditName, 2, 0, 1, 2);
  layoutMain->addWidget(checkPublicRoom, 3, 0, 1, 2);
  layoutMain->addWidget(labelPassword, 4, 0, 1, 2);
  layoutMain->addWidget(lineeditPassword, 5, 0);
  layoutMain->addWidget(buttonShow, 5, 1);
  layoutMain->addWidget(buttonValidate, 6, 0, 1, 2);

  this->setWindowTitle(tr("Room creation"));
  layoutMain->setAlignment(Qt::AlignTop);
  lineeditPassword->setDisabled(true);
  lineeditPassword->setStyleSheet("border: 1px solid #292929; color: #292929;");
  labelPassword->setStyleSheet("color: #292929;");
  buttonShow->setIcon(SUtils::getInstance()->getPixmap("hideOFF"));
  lineeditPassword->setEchoMode(QLineEdit::Password);
  checkPublicRoom->setCursor(Qt::PointingHandCursor);
  buttonValidate->setCursor(Qt::PointingHandCursor);
  buttonShow->setCursor(Qt::PointingHandCursor);
  SUtils::getInstance()->setFontOnWidget(labelTitle, 1.5);

  connect(buttonShow, SIGNAL(clicked()), this, SLOT(toggleShow()));
  connect(checkPublicRoom, SIGNAL(stateChanged(int)), this, SLOT(setIsRoomPublic(int)));
  connect(buttonValidate, SIGNAL(clicked()), this, SLOT(validButtonClicked()));
}

void NewRoomDialog::setIsRoomPublic(int boxState)
{
  if (boxState == 2)
  {
    lineeditPassword->setDisabled(false);
    buttonShow->setDisabled(false);
    lineeditPassword->setStyleSheet("border: 1px solid white; color: white; ");
    labelPassword->setStyleSheet("color: white;");
    if (showPass)
    {
      buttonShow->setIcon(SUtils::getInstance()->getPixmap("show"));
    }
    else
    {
      buttonShow->setIcon(SUtils::getInstance()->getPixmap("hide"));
    }
  }
  else
  {
    lineeditPassword->setDisabled(true);
    buttonShow->setDisabled(true);
    lineeditPassword->setStyleSheet("border: 1px solid #292929; color: #292929;");
    labelPassword->setStyleSheet("color: #292929;");
    if (showPass)
    {
      buttonShow->setIcon(SUtils::getInstance()->getPixmap("showOFF"));
    }
    else
    {
      buttonShow->setIcon(SUtils::getInstance()->getPixmap("hideOFF"));
    }
  }
}

void NewRoomDialog::validButtonClicked()
{
  QString name = lineeditName->text();
  if (name.isEmpty())
  {
    return;
  }

  QString pass = "";
  if (checkPublicRoom->isChecked())
  {
    pass = lineeditPassword->text();
    if (pass.isEmpty())
    {
      return;
    }
  }

  connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(applyRequest(QString)));
  req->createRoom(this, name, pass);
}

void NewRoomDialog::applyRequest(QString request)
{
  request.replace("\n", "");
  if (request != "done")
  {
    return;
  }
  emit newCurrentRoom(lineeditName->text());
  this->close();
}

void NewRoomDialog::toggleShow()
{
  if (showPass)
  {
    showPass = false;
    buttonShow->setIcon(SUtils::getInstance()->getPixmap("hide"));
    lineeditPassword->setEchoMode(QLineEdit::Password);
  }
  else
  {
    showPass = true;
    buttonShow->setIcon(SUtils::getInstance()->getPixmap("show"));
    lineeditPassword->setEchoMode(QLineEdit::Normal);
  }
}