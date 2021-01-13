#include "Rooms.h"

Rooms::Rooms(QWidget* parent)
  : QDialog(parent)
{
  build();
}

void Rooms::build()
{
  QVBoxLayout* layout = new QVBoxLayout(this);
  QLabel* title = new QLabel("Rooms", this);
  currentRoom = new QLabel("Current room: None", this);
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

  area->setWidgetResizable(true);

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
}

void Rooms::setRoomList(QString request)
{
  QJsonObject jsonObj((QJsonDocument::fromJson(request.toUtf8()).object()));
  int size = jsonObj.size();
  QStringList roomNames = jsonObj.keys();

  for (const QString& room : roomNames)
  {
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* labelRoomName = new QLabel(room, this);
    QLabel* labelIsLock = new QLabel(this);
    QPushButton* buttonJoin = new QPushButton("join", this);

    layoutArea->addLayout(layout);
    layout->addWidget(labelRoomName);
    layout->addWidget(labelIsLock);
    layout->addWidget(buttonJoin, Qt::AlignRight);

    QString password = jsonObj.value(room).toString();

    if (password != "")
    {
      labelIsLock->setText("Lock");
    }
    buttonJoin->setObjectName(password);
    passwordList.at(room) = password; // SET PASSWORD MAP
}