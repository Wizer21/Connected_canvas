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

QStringList* LayerList::getList()
{
  return &displayedUsers;
}

void LayerList::clearList()
{
  displayedUsers.clear();
  userPosition.clear();
  qDeleteAll(widgetList.begin(), widgetList.end());
  widgetList.clear();
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
      if (i + 1 != sizeList)
      {
        userPosition.move(i, i + 1);
        reBuild();
        updateDisplayedList();
        return;
      }
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
      if (i != 0)
      {
        userPosition.move(i, i - 1);
        reBuild();
        updateDisplayedList();
        return;
      }
    }
  }
}

void LayerList::toggleVisible()
{
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  QString userName = button->objectName();

  for (std::pair<QString, bool>& pair : userPosition)
  {
    if (pair.first == userName)
    {
      if (pair.second)
      {
        pair.second = false;
        SUtils::getInstance()->setIconOnButton(button, "hide", 1, 1);
      }
      else
      {
        pair.second = true;
        SUtils::getInstance()->setIconOnButton(button, "show", 1, 1);
      }
      updateDisplayedList();
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

    mainLayout->insertWidget(0, widgetUser);
    widgetUser->setLayout(layoutUser);
    layoutUser->addWidget(labelUserName, 0, 0, 2, 1);
    layoutUser->addWidget(buttonShow, 0, 1, 2, 1);
    layoutUser->addWidget(buttonUp, 0, 2);
    layoutUser->addWidget(buttonDown, 1, 2);

    buttonShow->setObjectName(pair.first);
    buttonUp->setObjectName(pair.first);
    buttonDown->setObjectName(pair.first);

    buttonShow->setCursor(Qt::PointingHandCursor);
    buttonUp->setCursor(Qt::PointingHandCursor);
    buttonDown->setCursor(Qt::PointingHandCursor);

    if (pair.second)
    {
      SUtils::getInstance()->setIconOnButton(buttonShow, "show", 1, 1);
    }
    else
    {
      SUtils::getInstance()->setIconOnButton(buttonShow, "hide", 1, 1);
    }

    layoutUser->setAlignment(Qt::AlignTop);

    buttonShow->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    widgetUser->setStyleSheet("background-color: #161616;");
    buttonShow->setStyleSheet("background-color: #212121;");
    buttonUp->setStyleSheet("background-color: #212121;");
    buttonDown->setStyleSheet("background-color: #212121;");

    connect(buttonShow, SIGNAL(clicked()), this, SLOT(toggleVisible()));
    connect(buttonUp, SIGNAL(clicked()), this, SLOT(userUp()));
    connect(buttonDown, SIGNAL(clicked()), this, SLOT(userDown()));
    widgetList.push_back(widgetUser);
  }
}