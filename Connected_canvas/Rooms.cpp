#include "Rooms.h"

Rooms::Rooms(QWidget* parent, QString roomName)
  : QDialog(parent)
{
  build(roomName);
  this->resize(500, 500);
}

void Rooms::build(QString roomName)
{
  QVBoxLayout* layout = new QVBoxLayout(this);
  QLabel* title = new QLabel(tr("Room list"), this);
  currentRoom = new QLabel(this);
  QScrollArea* area = new QScrollArea(this);
  QWidget* widgetArea = new QWidget(this);
  layoutArea = new QVBoxLayout(this);

  QPushButton* buttonNewRoom = new QPushButton("New Room", this);

  this->setLayout(layout);
  layout->addWidget(title);
  layout->addWidget(currentRoom);
  layout->addWidget(area);
  area->setWidget(widgetArea);
  widgetArea->setLayout(layoutArea);
  layout->addWidget(buttonNewRoom);

  layoutArea->setAlignment(Qt::AlignTop);
  area->setWidgetResizable(true);
  SUtils::getInstance()->setFontOnWidget(title, 1.5);
  buttonNewRoom->setCursor(Qt::PointingHandCursor);
  this->setWindowTitle(tr("Room list"));

  if (roomName != "")
  {
    currentRoom->setText(QString("Current room: %1").arg(roomName));
  }
  else
  {
    currentRoom->setText("Current room: None");
  }

  connect(buttonNewRoom, SIGNAL(clicked()), this, SLOT(newRoomClicked()));

  req = new Requester();
  connect(req, SIGNAL(transfertRequest(QString)), this, SLOT(setRoomList(QString)));
  req->roomListPassword(this);
}

void Rooms::newRoomClicked()
{
  NewRoomDialog* room = new NewRoomDialog(this);
  connect(room, SIGNAL(newCurrentRoom(QString)), this, SLOT(setCurrentRoom(QString)));
  room->exec();
}

void Rooms::setCurrentRoom(QString roomName)
{
  currentRoom->setText(roomName);
  emit sendNewRoom(roomName);
  this->close();
}

void Rooms::setRoomList(QString request)
{
  QJsonObject jsonObj((QJsonDocument::fromJson(request.toUtf8()).object()));
  QStringList roomNames = jsonObj.keys();

  for (const QString& room : roomNames)
  {
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* labelRoomName = new QLabel(room, this);
    QLabel* labelIsLock = new QLabel(this);
    QPushButton* buttonJoin = new QPushButton("join", this);

    layoutArea->addLayout(layout);
    layout->addWidget(labelRoomName, Qt::AlignLeft);
    layout->addWidget(labelIsLock, Qt::AlignRight);
    layout->addWidget(buttonJoin, Qt::AlignRight);
    buttonJoin->setCursor(Qt::PointingHandCursor);

    QString password = jsonObj.value(room).toString();

    if (password != "")
    {
      labelIsLock->setText("Lock");
    }
    buttonJoin->setObjectName(room);
    passwordList.insert(std::pair<QString, QString>(room, password)); // SET PASSWORD MAP
    connect(buttonJoin, SIGNAL(clicked()), this, SLOT(joinRoomClicked()));
  }
}

void Rooms::joinRoomClicked()
{
  QString pass = passwordList.at(sender()->objectName());
  if (pass != "")
  {
    PassWordDialog* passDialog = new PassWordDialog(this, sender()->objectName(), pass);
    connect(passDialog, SIGNAL(roomPasswordSucces(QString)), this, SLOT(setCurrentRoom(QString)));
    passDialog->exec();
  }
  else
  {
    setCurrentRoom(sender()->objectName());
  }
}
