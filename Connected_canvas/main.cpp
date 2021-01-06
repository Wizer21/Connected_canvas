#include "Connected_canvas.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connected_canvas w;
    w.show();
    return a.exec();
}
