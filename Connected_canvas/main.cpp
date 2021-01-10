#include "Connected_canvas.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  Connected_canvas w;

  QFile qss(":/Connected_canvas/files/theme.qss");
  if (qss.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QTextStream text(&qss);
    a.setStyleSheet(text.readAll());
    qss.close();
  }

  w.show();
  return a.exec();
}
