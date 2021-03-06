#include "Connected_canvas.h"
#include "stdafx.h"

Connected_canvas::Connected_canvas(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  userName = "";
  paint = true;

  build();
  this->resize(1500, 1000);
}

void Connected_canvas::build()
{
  QMenuBar* barMain = new QMenuBar(this);
  QMenu* menuMore = new QMenu(tr("More"), this);
  QWidgetAction* actionLogIn = new QWidgetAction(this);
  actionFriends = new QWidgetAction(this);
  actionRooms = new QWidgetAction(this);
  QLabel* labelActionLog = new QLabel(tr("Login"), this);
  labelActionFriend = new QLabel(tr("Friends"), this);
  labelActionRoom = new QLabel(tr("Rooms"), this);

  QWidget* widgetCentral = new QWidget(this);
  QGridLayout* layoutMain = new QGridLayout(this);

  QWidget* widgetRoom = new QWidget(this);
  QGridLayout* layoutRoom = new QGridLayout(this);
  labelPseudo = new QLabel(tr("Offline"), this);
  labelRoomName = new QLabel(this);
  LayerList* layers = new LayerList(this);

  myPen = new QPen();
  penBuilder = new PenBuilder(this, myPen, &paint);

  QGraphicsView* viewMain = new QGraphicsView(this);
  sceneMain = new GraphicScene(this, myPen, &paint, layers, viewMain);

  this->setCentralWidget(widgetCentral);
  widgetCentral->setLayout(layoutMain);

  this->setMenuBar(barMain);
  barMain->addMenu(menuMore);
  actionLogIn->setDefaultWidget(labelActionLog);
  actionFriends->setDefaultWidget(labelActionFriend);
  actionRooms->setDefaultWidget(labelActionRoom);

  menuMore->addAction(actionLogIn);
  menuMore->addAction(actionFriends);
  menuMore->addAction(actionRooms);

  layoutMain->addWidget(widgetRoom, 0, 0);
  widgetRoom->setLayout(layoutRoom);
  layoutRoom->addWidget(labelPseudo, 0, 0);
  layoutRoom->addWidget(labelRoomName, 0, 1);
  layoutRoom->addWidget(layers, 1, 0, 1, 2);

  layoutMain->addWidget(penBuilder, 1, 0);

  layoutMain->addWidget(viewMain, 0, 1, 2, 1);

  // THEME
  viewMain->setScene(sceneMain);
  layoutMain->setColumnStretch(0, 0);
  layoutMain->setColumnStretch(1, 1);
  layoutMain->setSpacing(0);
  layoutMain->setContentsMargins(0, 0, 0, 0);

  viewMain->setFixedSize(1010, 1010);
  actionFriends->setEnabled(false);
  actionRooms->setEnabled(false);
  labelActionLog->setStyleSheet("QLabel::hover{border-left: 3px solid white}");
  labelActionFriend->setStyleSheet("color: 292929");
  labelActionRoom->setStyleSheet("color: 292929");
  labelActionLog->setContentsMargins(5, 5, 5, 5);
  labelActionFriend->setContentsMargins(5, 5, 5, 5);
  labelActionRoom->setContentsMargins(5, 5, 5, 5);
  labelActionLog->setCursor(Qt::PointingHandCursor);
  menuMore->setContentsMargins(0, 0, 0, 0);
  menuMore->setStyleSheet("padding: 0px;");
  this->setStyleSheet("background-color: #212121;");
  viewMain->setStyleSheet("border: 0px solid white; background-color: #161616");

  // CONNECT TO DATA
  req = new Requester();
  connect(req, SIGNAL(transfertLog(QString)), this, SLOT(setName(QString)));

  connect(penBuilder, SIGNAL(penSizeChanged()), this, SLOT(updateCursorOnPenSize()));
  connect(actionLogIn, SIGNAL(triggered()), this, SLOT(logInTriggered()));
  connect(actionFriends, SIGNAL(triggered()), this, SLOT(friendsTriggered()));
  connect(actionRooms, SIGNAL(triggered()), this, SLOT(roomsTriggered()));
  connect(sceneMain, SIGNAL(penSizeChanged(int)), this, SLOT(newPenSize(int)));
}

void Connected_canvas::setName(QString newName)
{
  labelPseudo->setText(newName);
  userName = newName;
}

void Connected_canvas::logInTriggered()
{
  AccountLog account;
  connect(&account, SIGNAL(transfertCurrentUser(QString)), this, SLOT(displayNewUser(QString)));
  account.exec();
}

void Connected_canvas::friendsTriggered()
{
  Friends friends(this, labelPseudo->text());
  friends.exec();
}

void Connected_canvas::roomsTriggered()
{
  Rooms* rooms = new Rooms(this, labelRoomName->text());
  connect(rooms, SIGNAL(sendNewRoom(QString)), this, SLOT(joinedRoom(QString)));
  rooms->exec();
}

void Connected_canvas::displayNewUser(QString newName)
{
  labelPseudo->setText(newName);
  userName = newName;

  actionFriends->setEnabled(true);
  actionRooms->setEnabled(true);

  labelActionFriend->setStyleSheet("QLabel::hover{border-left: 3px solid white; color: white;}");
  labelActionRoom->setStyleSheet("QLabel::hover{border-left: 3px solid white; color: white;}");
  labelActionFriend->setCursor(Qt::PointingHandCursor);
  labelActionRoom->setCursor(Qt::PointingHandCursor);
}

void Connected_canvas::closeEvent(QCloseEvent* event)
{
  sceneMain->closeThread(); // WHEN PROGROM READY, THIS WILL LOGOUT FROM THE CURRENT ROOM
  this->hide();
  qApp->processEvents();
  req->logOut(this, labelPseudo->text());
}

void Connected_canvas::joinedRoom(QString newRoomName)
{
  labelRoomName->setText(newRoomName);
  sceneMain->joinedRoom(newRoomName, userName);
}

void Connected_canvas::newPenSize(int val)
{
  penBuilder->setPenSizeFromWheel(val);
}

void Connected_canvas::updateCursorOnPenSize()
{
  sceneMain->drawCursor();
}

void Connected_canvas::updateUi()
{
  penBuilder->setSelecter();
}