#include "NewRoomDialog.h"

NewRoomDialog::NewRoomDialog(QWidget* parent)
  : QDialog(parent)
{
  build();
  this->resize(200, 200);
}

void NewRoomDialog::build()
{
  QVBoxLayout* layoutMain = new QVBoxLayout(this);
  QLabel* labelTitle = new QLabel(tr("New Room"), this);
  QLabel* labelRoomName = new QLabel(tr("Room name"), this);
  lineeditName = new QLineEdit(this);
  checkPublicRoom = new QCheckBox(tr("Private room"), this);
  labelPassword = new QLabel(tr("Room password"), this);
  lineeditPassword = new QLineEdit(this);
  QPushButton* buttonValidate = new QPushButton(tr("Validate"), this);

  req = new Requester();

  this->setLayout(layoutMain);
  layoutMain->addWidget(labelTitle);
  layoutMain->addWidget(labelRoomName);
  layoutMain->addWidget(lineeditName);
  layoutMain->addWidget(checkPublicRoom);
  layoutMain->addWidget(labelPassword);
  layoutMain->addWidget(lineeditPassword);
  layoutMain->addWidget(buttonValidate);

  layoutMain->setAlignment(Qt::AlignTop);
  lineeditPassword->setDisabled(true);
  lineeditPassword->setStyleSheet("border: 1px solid #292929; color: #292929;");
  labelPassword->setStyleSheet("color: #292929;");

  connect(checkPublicRoom, SIGNAL(stateChanged(int)), this, SLOT(setIsRoomPublic(int)));
  connect(buttonValidate, SIGNAL(clicked()), this, SLOT(validButtonClicked()));
}

void NewRoomDialog::setIsRoomPublic(int boxState)
{
  if (boxState == 2)
  {
    lineeditPassword->setDisabled(false);
    lineeditPassword->setStyleSheet("border: 1px solid white; color: white; ");
    labelPassword->setStyleSheet("color: white;");
  }
  else
  {
    lineeditPassword->setDisabled(true);
    lineeditPassword->setStyleSheet("border: 1px solid #292929; color: #292929;");
    labelPassword->setStyleSheet("color: #292929;");
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