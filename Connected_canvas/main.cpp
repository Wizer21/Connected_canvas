#include "Connected_canvas.h"
#include <QtWidgets/QApplication>
#include "SUtils.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

  QRect rect = QRect(a.primaryScreen()->availableGeometry()); // SCREEN SIZE
  std::pair<int, int> resolution(rect.width(), rect.height());

  int fontSize = round(resolution.first / 110);
  QString fontQSS = "QWidget{ font-size:" + QString::number(fontSize) + "px;}"; // FONT SIZE ON SCREEN SIZE

  SUtils::getInstance()->pushResolution(resolution, fontSize);

  QFile qss(":/Connected_canvas/files/theme.qss");
  if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) // SET QSS
  {
    QTextStream text(&qss);
    a.setStyleSheet(fontQSS + text.readAll());
    qss.close();
  }

  Connected_canvas w;
  w.show();
  return a.exec();
}
