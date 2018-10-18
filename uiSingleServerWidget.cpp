#include "uiSingleServerWidget.h"

uiSingleServerWidget::uiSingleServerWidget(int widgetNum, QWidget* parent) :QWidget(parent)
{
  m_pServer = new QTcpServer(this);
  m_pTimer = new QTimer(this);
  m_iWidgetNum = widgetNum;
  ui.setupUi(this);
  connect(ui.checkBox_Server, &QCheckBox::stateChanged, this, &uiSingleServerWidget::slotOpenSystem);
  connect(ui.checkBox_Server, &QCheckBox::stateChanged, this, &uiSingleServerWidget::slotReadSendDataFromText);
  //connect(m_pTimer, &QTimer::timeout, this, &uiSingleServerWidget::slotCloseServer);
  //m_pTimer->start(200);
}

void uiSingleServerWidget::slotOpenSystem()
{
  if(ui.checkBox_Server->isChecked())
  {
    writeConfig();
    m_iPort = ui.spinBox_port->value();
    int _time = ui.spinBox_Timeout->value();
    connect(m_pTimer, &QTimer::timeout, this, &uiSingleServerWidget::slotOpenOrCloseServer);
    m_pTimer->start(_time);
  }
  else
  {
    m_pTimer->stop();
    disconnect(m_pTimer, &QTimer::timeout, this, &uiSingleServerWidget::slotOpenOrCloseServer);
    if (m_pServer&&m_pServer->isListening())
    {
      for (int i = 0; i < m_vSocketGroup.length(); ++i)
      {
        if (m_vSocketGroup[i]->isOpen())
        {
          m_vSocketGroup[i]->close();
          --i;
        }
      }
      m_pServer->close();
      disconnect(m_pServer, &QTcpServer::newConnection, this, &uiSingleServerWidget::slotNewClient);
    }
  }
}

void uiSingleServerWidget::slotReadSendDataFromText()
{
    m_sFileAddress = ui.lineEdit_FileAddr->text();
    qDebug() << m_sFileAddress;
    QFile* _textFile = new QFile(m_sFileAddress);
    if (_textFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
      QTextStream in(_textFile);
      QString _Line = in.readLine();
      QString _temData = "";
      while (!_Line.isNull())
      {
        _temData.append(_Line);
        _Line = in.readLine();
      }
      m_slSendData = _temData.split("|");
    }
}

void uiSingleServerWidget::slotOpenServer(int port)
{
  
}

void uiSingleServerWidget::slotOpenOrCloseServer()
{
  if (m_pServer&&m_pServer->isListening())
  {
    for (int i = 0; i < m_vSocketGroup.length(); ++i)
    {
      if (m_vSocketGroup[i]->isOpen())
      {
        m_vSocketGroup[i]->close();
        --i;
      }
    }
    m_pServer->close();
    disconnect(m_pServer, &QTcpServer::newConnection, this, &uiSingleServerWidget::slotNewClient);
  }
  else
  {
    if (m_pServer->listen(QHostAddress::Any, m_iPort))
    {
      qDebug() << "ServerStart" << m_iPort;
    }
    connect(m_pServer, &QTcpServer::newConnection, this, &uiSingleServerWidget::slotNewClient);
  }
}

void uiSingleServerWidget::writeConfig()
{
//  _settings.setValue()
  g_Settings.beginGroup(QString("Server") + QString::number(m_iWidgetNum, 10));
  g_Settings.setValue("Port", ui.spinBox_port->value());
  g_Settings.setValue("Address", ui.lineEdit_FileAddr->text());
  g_Settings.setValue("Time", ui.spinBox_Timeout->value());
  g_Settings.endGroup();
}

void uiSingleServerWidget::initData()
{
  g_Settings.beginGroup(QString("Server") + QString::number(m_iWidgetNum, 10));
  QString strPort = "Port";
  if (g_Settings.value(strPort).isNull())
    g_Settings.setValue(strPort, 8080);
  ui.spinBox_port->setValue(g_Settings.value("Port").toInt());
  QString strTime = "Time";
  if (g_Settings.value(strTime).isNull())
    g_Settings.setValue(strTime, 60000);
  ui.spinBox_Timeout->setValue(g_Settings.value("Time").toInt());
  QString strAddress = "Address";
  if (g_Settings.value(strAddress).isNull())
    g_Settings.setValue(strAddress, "/");
  ui.lineEdit_FileAddr->setText(g_Settings.value("Address").toString());
  g_Settings.endGroup();
}

void uiSingleServerWidget::slotNewClient()
{
  m_vSocketGroup.append(m_pServer->nextPendingConnection());
  m_vTimerGroup.append(new QTimer(this));
  connect(m_vSocketGroup.last(), &QTcpSocket::disconnected, this, &uiSingleServerWidget::slotDisconnection);
  connect(m_vSocketGroup.last(), &QTcpSocket::disconnected, m_vSocketGroup.last(), &QTcpSocket::deleteLater);
  connect(m_vTimerGroup.last(), &QTimer::timeout, this, &uiSingleServerWidget::slotSendData);
  m_vTimerGroup.last()->start(200);
}

void uiSingleServerWidget::slotDisconnection()
{
  QTcpSocket* pTemSocket = qobject_cast<QTcpSocket*>(sender());
  int _index = m_vSocketGroup.indexOf(pTemSocket);
  m_vTimerGroup[_index]->stop();
  m_vTimerGroup.remove(_index);
  m_vSocketGroup.removeOne(pTemSocket);
}

void uiSingleServerWidget::slotSendData()
{
  QTimer* pTimer = qobject_cast<QTimer*>(sender());
  int _index = m_vTimerGroup.indexOf(pTimer);
  if (m_vSocketGroup[_index]->isOpen())
  {
    if (m_iflag < m_slSendData.length())
    {
      QDateTime nowtime = QDateTime::currentDateTime();
      QString nowTime = nowtime.toString("hhmmss.zzzz");
      //     m_sendData[i].replace(12, 22, nowTime);
      for (int j = 0; j < 11; ++j)
      {
        m_slSendData[m_iflag][14 + j] = nowTime[j];
      }
      qDebug() << m_slSendData[m_iflag];
      m_vSocketGroup[_index]->write(m_slSendData[m_iflag].toLatin1().data(), m_slSendData[m_iflag].length());
      m_vSocketGroup[_index]->waitForBytesWritten(100);
      ++m_iflag;
    }
    else
    {
      m_iflag = 0;
    }
  }
}

