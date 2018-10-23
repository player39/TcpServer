
#include "uiServerWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  uiServerWidget* w = new uiServerWidget;
  w->setWindowFlags(Qt::Window);
  w->show();
  return a.exec();
}
