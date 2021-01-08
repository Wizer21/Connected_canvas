#include "Connected_canvas.h"
#include "stdafx.h"

Connected_canvas::Connected_canvas(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  build();
  logIn();
  loadData();
}

void Connected_canvas::build()
{
  QWidget* widgetCentral = new QWidget(this);
  QGridLayout* layoutMain = new QGridLayout(this);

  QWidget* widgetRoom = new QWidget(this);
  QGridLayout* layoutRoom = new QGridLayout(this);
  labelPseudo = new QLabel("peudo", this);
  QLabel* labelId = new QLabel("myid", this);
  QLabel* labelRoomId = new QLabel("roomid", this);
  QScrollArea* areaUserRoom = new QScrollArea(this);
  QWidget* widgetArea = new QWidget(this);
  QVBoxLayout* layoutArea = new QVBoxLayout(this);

  QWidget* widgetDraw = new QWidget(this);

  QWidget* widgetLayers = new QWidget(this);

  QWidget* widgetCanvas = new QWidget(this);

  this->setCentralWidget(widgetCentral);
  widgetCentral->setLayout(layoutMain);

  layoutMain->addWidget(widgetRoom, 0, 0);
  widgetRoom->setLayout(layoutRoom);
  layoutRoom->addWidget(labelPseudo, 0, 0);
  layoutRoom->addWidget(labelId, 1, 0);
  layoutRoom->addWidget(labelRoomId, 0, 1);
  layoutRoom->addWidget(areaUserRoom, 2, 0, 1, 2);
  areaUserRoom->setWidget(widgetArea);
  widgetArea->setLayout(layoutArea);

  // CONNECT TO DATA
  req = new Requester;
  connect(req, SIGNAL(transfertLog(QString)), this, SLOT(setName(QString)));
}

void Connected_canvas::loadData()
{
}

void logIn()
{
  auto logFile{QCoreApplication::applicationDirPath() + QDir::separator() + "log.json"};
  if (QFile(logFile).exists())
  {
    QJsonDocument jsonDoc(QJsonDocument::fromJson(logFile.toUtf8()));
    QJsonObject jsonObj = jsonDoc.object();

    if (jsonObj.contains("pseudo") && jsonObj.contains("pass"))
    {
      jsonObj.langue = jsonObj["langue"].toString();
      jsonObj.theme = jsonObj["theme"].toString();
    }
  }
}

void Connected_canvas::setName(QString newName)
{
  labelPseudo->setText(newName);
}