
#ifndef _UISINGLESERVERWIDGET_H
#define _UISINGLESERVERWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCore/QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QTimer>
#include <QtWidgets/QCheckBox>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QDateTime>
#include <QtCore/QSettings>
#include "ui_uiSingleServerWidget.h"
#include "Config.h"

class uiSingleServerWidget :public QWidget
{

  Q_OBJECT

public:
  uiSingleServerWidget(int widgetNum, QWidget* parent = Q_NULLPTR);
  void writeConfig();
  void initData();

private:
  Ui::ui_SingleServerWidget ui;
  QTcpServer* m_pServer = Q_NULLPTR;
  QVector<QTcpSocket*> m_vSocketGroup;
  QTimer *m_pTimer = Q_NULLPTR;
  QVector<QTimer*> m_vTimerGroup;
  QStringList m_slSendData;
  QString m_sFileAddress="";
  int m_iflag = 0;
  int m_iPort = 0;
  int m_iTime = 0;
  int m_iWidgetNum = 0;

public slots:
  void slotOpenSystem();
  void slotNewClient();
  void slotSendData();
  void slotDisconnection();
  void slotReadSendDataFromText();
  void slotOpenServer(int port);
  void slotOpenOrCloseServer();
};

#endif
