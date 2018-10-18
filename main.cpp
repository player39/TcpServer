#include "TcpServer.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  jyTcpServer w;
  w.show();
  return a.exec();
}
