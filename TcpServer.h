#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#include <QtWidgets/QWidget>
#include <QtNetwork/QTcpServer>
#include <QtCore/QVector>
#include <QtWidgets/QPushButton>
#include <QtNetwork/QTcpServer>
#include <QtCore/QFile>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QSettings>
#include "ui_TcpServerCUI.h"
#include "uiSingleServerWidget.h"
#include "Config.h"

class jyTcpServer :public QWidget
{
  Q_OBJECT
public:
  jyTcpServer();
  void writeFile();
  void readConfigFile();
  void initWidget();

private:
  Ui::TcpServerClass ui;
  QStringList m_slConfigData;
  QVector<uiSingleServerWidget*> m_vServerWidgetGroup;
  int m_iServerNum = 4;
  int m_iPort = 8080;
  int m_iTime = 60000;
  QString m_sAddress = "/";

signals:

public slots:

};


#endif
