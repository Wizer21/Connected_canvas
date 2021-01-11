#include "Rooms.h"

Rooms::Rooms(QWidget* parent)
  : QDialog(parent)
{
  build();
  loadRooms();
}

void Rooms::build()
{
  QVBoxLayout* layout = new QVBoxLayout(this);
  QLabel* title = new QLabel("Rooms", this);
  currentRoom = new QLabel("Current room: None", this);
  QScrollArea* area = new QScrollArea(this);
  QWidget* widgetArea = new QWidget(this);
  QVBoxLayout* layoutArea = new QVBoxLayout(this);

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
}

void Rooms::loadRooms()
{
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
}