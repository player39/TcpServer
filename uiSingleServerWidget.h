
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
  //�ӱ��ض������ļ�
  void readDataFromTxt();
  //д�������ļ�
  void writeConfig();
  //��server�ر�ʱ�ر�socket
  void closeSocket();
  //У���
  std::string creatSum(const QString& strSendData);
  void slotTimeout();
  void slotStateChanged(int iValue);
  //��������
  void slotSendData();
  void slotNewClient();
  void slotDisconnection();

private:
  Ui::uiSingleServerWidget ui;
  class QTimer* m_pTimer;
  class QTcpServer* m_pTcpServer;
  //��ʾ���widget��id
  int m_iWidgetID = -1;
  QTimer* m_pSocketTimer = Q_NULLPTR;
  std::string m_sAddress = "";
  std::string m_sSendDataGroup = "";
  //��Ҫ���͵�������
  QStringList m_strSendData;
  //�������ݵ��±�
  int m_iSendDataNum = 0;
  std::vector<QTcpSocket*> m_vSocketGroup;
};

#endif  // _SINGLESERVERWIDGET_H
