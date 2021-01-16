#include "LayerList.h"

LayerList::LayerList(QWidget* parent)
  : QScrollArea(parent)
{
  QWidget* widgetMain = new QWidget(this);
  mainLayout = new QVBoxLayout(this);

  this->setWidget(widgetMain);
  widgetMain->setLayout(mainLayout);

  mainLayout->setAlignment(Qt::AlignTop);
  this->setWidgetResizable(true);
}

void LayerList::clearList()
{
  displayedUsers.clear();
  userPosition.clear();
}

void LayerList::newUser(QString userName)
{
  userPosition.append({userName, true});
  displayedUsers.append(userName);
}

void LayerList::leavedUser(QString userName)
{
  int sizeList = int(userPosition.size());
  for (int i = 0; i < sizeList; i++)
  {
    if (userPosition.at(i).first == userName)
    {
      userPosition.erase(userPosition.begin() + i);
      return;
    }
  }
  updateDisplayedList();
}

void LayerList::updateDisplayedList()
{
  displayedUsers.clear();
  for (const std::pair<QString, bool> pair : userPosition)
  {
    if (pair.second)
    {
      displayedUsers.append(pair.first);
    }
  }
}

void LayerList::userUp()
{
  QString userName = sender()->objectName();
  int sizeList = int(userPosition.size());
  for (int i = 0; i < sizeList; i++)
  {
    if (userPosition.at(i).first == userName)
    {
      userPosition.move(i, i + 1);
      return;
    }
  }
}

void LayerList::userDown()
{
  QString userName = sender()->objectName();
  int sizeList = int(userPosition.size());
  for (int i = 0; i < sizeList; i++)
  {
    if (userPosition.at(i).first == userName)
    {
      userPosition.move(i, i - 1);
      return;
    }
  }
}

void LayerList::toggleVisible()
{
  QString userName = sender()->objectName();

  for (std::pair<QString, bool> pair : userPosition)
  {
    if (pair.first == userName)
    {
      if (pair.second)
      {
        pair.second = false;
      }
      else
      {
        pair.second = true;
      }
      return;
    }
  }
}

void LayerList::reBuild()
{
  qDeleteAll(widgetList.begin(), widgetList.end());
  widgetList.clear();

  for (const std::pair<QString, bool> pair : userPosition)
  {
    QWidget* widgetUser = new QWidget(this);
    QGridLayout* layoutUser = new QGridLayout(this);
    QLabel* labelUserName = new QLabel(pair.first, this);
    QPushButton* buttonShow = new QPushButton(this);
    QPushButton* buttonUp = new QPushButton("up", this);
    QPushButton* buttonDown = new QPushButton("down", this);

    mainLayout->addWidget(widgetUser);
    widgetUser->setLayout(layoutUser);
    layoutUser->addWidget(labelUserName, 0, 0, 2, 1);
    layoutUser->addWidget(buttonShow, 0, 1, 2, 1);
    layoutUser->addWidget(buttonUp, 0, 2);
    layoutUser->addWidget(buttonDown, 1, 2);

    buttonShow->setObjectName(pair.first);
    buttonUp->setObjectName(pair.first);
    buttonDown->setObjectName(pair.first);

    if (pair.second)
    {
      buttonShow->setText("Show");
    }
    else
    {
      buttonShow->setText("Hide");
    }

    layoutUser->setAlignment(Qt::AlignTop);

    buttonShow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonUp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonDown->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(buttonShow, SIGNAL(clicked()), this, SLOT(toggleVisible()));
    connect(buttonUp, SIGNAL(clicked()), this, SLOT(userUp()));
    connect(buttonDown, SIGNAL(clicked()), this, SLOT(userDown()));
    widgetList.push_back(widgetUser);
  }
}