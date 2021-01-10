#include "Connected_canvas.h"
#include "stdafx.h"

Connected_canvas::Connected_canvas(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  build();
  logIn();
  this->resize(1500, 1000);
}

void Connected_canvas::build()
{
  QMenuBar* barMain = new QMenuBar(this);
  QAction* actionLogIn = new QAction(tr("Login"), this);
  QAction* actionFriends = new QAction(tr("Friends"), this);

  QWidget* widgetCentral = new QWidget(this);
  QGridLayout* layoutMain = new QGridLayout(this);

  QWidget* widgetRoom = new QWidget(this);
  QGridLayout* layoutRoom = new QGridLayout(this);
  labelPseudo = new QLabel("Offline", this);
  QLabel* labelId = new QLabel("myid", this);
  QLabel* labelRoomId = new QLabel("roomid", this);
  QScrollArea* areaUserRoom = new QScrollArea(this);
  QWidget* widgetArea = new QWidget(this);
  QVBoxLayout* layoutArea = new QVBoxLayout(this);

  myPen = new QPen();
  PenBuilder* penBuilder = new PenBuilder(this, myPen);

  //QWidget* widgetLayers = new QWidget(this);

  Canvas* sceneMain = new Canvas(this, myPen);

  this->setCentralWidget(widgetCentral);
  widgetCentral->setLayout(layoutMain);

  this->setMenuBar(barMain);
  barMain->addAction(actionLogIn);
  barMain->addAction(actionFriends);

  layoutMain->addWidget(widgetRoom, 0, 0);
  widgetRoom->setLayout(layoutRoom);
  layoutRoom->addWidget(labelPseudo, 0, 0);
  layoutRoom->addWidget(labelId, 1, 0);
  layoutRoom->addWidget(labelRoomId, 0, 1);
  layoutRoom->addWidget(areaUserRoom, 2, 0, 1, 2);
  areaUserRoom->setWidget(widgetArea);
  widgetArea->setLayout(layoutArea);

  layoutMain->addWidget(penBuilder, 1, 0);

  layoutMain->addWidget(sceneMain, 0, 1, 2, 1);

  // THEME
  layoutMain->setColumnStretch(0, 0);
  layoutMain->setColumnStretch(1, 1);
  sceneMain->resize(1000, 1000);

  // CONNECT TO DATA
  req = new Requester();
  connect(req, SIGNAL(transfertLog(QString)), this, SLOT(setName(QString)));

  connect(actionLogIn, SIGNAL(triggered()), this, SLOT(logInTriggered()));
  connect(actionFriends, SIGNAL(triggered()), this, SLOT(friendsTriggered()));
}

void Connected_canvas::logIn()
{
  auto logFile{QCoreApplication::applicationDirPath() + QDir::separator() + "log.json"};
  if (QFile(logFile).exists())
  {
    QJsonDocument jsonDoc(QJsonDocument::fromJson(logFile.toUtf8()));
    QJsonObject jsonObj = jsonDoc.object();

    //if (jsonObj.contains("pseudo") && jsonObj.contains("pass"))
    //{
    //  jsonObj.langue = jsonObj["langue"].toString();
    //  jsonObj.theme = jsonObj["theme"].toString();
    //}
  }
}

void Connected_canvas::setName(QString newName)
{
  labelPseudo->setText(newName);
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

void Connected_canvas::displayNewUser(QString newName)
{
  labelPseudo->setText(newName);
}

void Connected_canvas::closeEvent(QCloseEvent* event)
{
  QMessageBox box(QMessageBox::NoIcon, " ", tr("Disconnecting...\nThis can take few seconds."), QMessageBox::NoButton, this, Qt::Dialog);
  box.show();

  qApp->processEvents();
  req->logOut(this, labelPseudo->text());
}