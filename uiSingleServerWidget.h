
#ifndef _SINGLESERVERWIDGET_H
#define _SINGLESERVERWIDGET_H

#include <iostream>
#include <QtWidgets/QWidget>
#include <QtCore/QSettings>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QDateTime>
#include <string>
#include <vector>
#include <stdio.h>
#include "ui_uiSingleServerWidget.h"

typedef std::vector<QTcpSocket*>::iterator pSocketItr;

class uiSingleServerWidget : public QWidget
{
public:
  uiSingleServerWidget(QWidget* parent = Q_NULLPTR);
  ~uiSingleServerWidget();

  void initWidget(int iID);
  //从本地读数据文件
  void readDataFromTxt();
  //写入配置文件
  void writeConfig();
  //在server关闭时关闭socket
  void closeSocket();
  //校验和
  std::string creatSum(const QString& strSendData);
  void slotTimeout();
  void slotStateChanged(int iValue);
  //发送数据
  void slotSendData();
  void slotNewClient();
  void slotDisconnection();

private:
  Ui::uiSingleServerWidget ui;
  class QTimer* m_pTimer;
  class QTcpServer* m_pTcpServer;
  //表示这个widget的id
  int m_iWidgetID = -1;
  QTimer* m_pSocketTimer = Q_NULLPTR;
  std::string m_sAddress = "";
  std::string m_sSendDataGroup = "";
  //将要发送的数据组
  QStringList m_strSendData;
  //发送数据的下标
  int m_iSendDataNum = 0;
  std::vector<QTcpSocket*> m_vSocketGroup;
};

#endif  // _SINGLESERVERWIDGET_H
