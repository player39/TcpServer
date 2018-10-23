
#include "uiSingleServerWidget.h"
#include <QtCore/QTimer>
#include "Config.h"

uiSingleServerWidget::uiSingleServerWidget(QWidget* parent /* = Q_NULLPTR */)
  : QWidget(parent)
{
  ui.setupUi(this);

  m_pTcpServer = new QTcpServer(this);
  m_pTimer = new QTimer(this);
  m_pSocketTimer = new QTimer(this);
  m_pSocketTimer->start(200);

  connect(m_pTimer, &QTimer::timeout, this, &uiSingleServerWidget::slotTimeout);
  connect(ui.checkBox, &QCheckBox::stateChanged, this, &uiSingleServerWidget::slotStateChanged);
  connect(m_pTcpServer, &QTcpServer::newConnection, this, &uiSingleServerWidget::slotNewClient);
  connect(m_pSocketTimer, &QTimer::timeout, this, &uiSingleServerWidget::slotSendData);
}

uiSingleServerWidget::~uiSingleServerWidget()
{

}

void uiSingleServerWidget::initWidget(int iID)
{
  m_iWidgetID = iID;
  char sName[100] = "";
  sprintf(sName, "Server%d", iID);
  ui.checkBox->setText(sName);

  g_Settings.beginGroup(sName);

  QString strPort = "Port";
  if (g_Settings.value(strPort).isNull())
    g_Settings.setValue(strPort, 8080);
  ui.spinBox_Port->setValue(g_Settings.value(strPort).toInt());

  QString strTimeout = "Timeout";
  if (g_Settings.value(strTimeout).isNull())
    g_Settings.setValue(strTimeout, 3000);
  ui.spinBox_Timeout->setValue(g_Settings.value(strTimeout).toInt());

  QString strEnable = "Enable";
  if (g_Settings.value(strEnable).isNull())
    g_Settings.setValue(strEnable, "False");
  ui.checkBox->setChecked(g_Settings.value(strEnable).toBool());

  QString strAddress = "Address";
  if (g_Settings.value(strAddress).isNull())
    g_Settings.setValue(strAddress, "");
  ui.lineEdit_Address->setText(g_Settings.value(strAddress).toString());

  g_Settings.endGroup();

  if (ui.checkBox->isChecked())
    readDataFromTxt();
}

std::string uiSingleServerWidget::creatSum(const QString& strSendData)
{
  int iResult = strSendData[1].unicode();
  for (int i = 2; strSendData[i] != '*'; ++i)
  {
    if(strSendData[i] == ']' || strSendData[i] == '$')
      continue;
    iResult ^= strSendData[i].unicode();
  }
  char sTemResult[10];
  sprintf(sTemResult, "%X", iResult);
  std::string sResult = sTemResult;
  return sResult;
}

void uiSingleServerWidget::slotTimeout()
{
  if (m_pTcpServer->isListening())
  {
    closeSocket();
    m_pTcpServer->close();
    ui.checkBox->setStyleSheet("color : red");
    //发送数据在QStringList中的下标清零
    m_iSendDataNum = 0;
  }
  else
  {
    m_pTcpServer->listen(QHostAddress::Any, ui.spinBox_Port->value());
    ui.checkBox->setStyleSheet("color : green");
  }
}

void uiSingleServerWidget::slotStateChanged(int iValue)
{
  writeConfig();

  if (ui.checkBox->isChecked())
  {
    readDataFromTxt();
    m_pTimer->start(ui.spinBox_Timeout->value());
  }
  else
  {
    if (m_pTcpServer->isListening())
    {
      closeSocket();
      m_pTcpServer->close();
      ui.checkBox->setStyleSheet("color : red");
    }
    m_pTimer->stop();
  }
}

void uiSingleServerWidget::slotSendData()
{
  for (pSocketItr itr = m_vSocketGroup.begin(); itr != m_vSocketGroup.end(); ++itr)
  {
    if(m_sSendDataGroup.length())
      m_strSendData = QString::fromStdString(m_sSendDataGroup).split('|');

    if ((*itr)->isOpen())
    {
      if (m_iSendDataNum < m_strSendData.length())
      {
        QDateTime qtimeNowDate = QDateTime::currentDateTime();
        QString strTime = qtimeNowDate.toString("hhmmss.zzzz");
        //时间生成
        char sTemSendData[100];
        sprintf(sTemSendData, m_strSendData[m_iSendDataNum].toStdString().c_str(), strTime.toStdString().c_str(), "%s");
        //校验和生成
        char sSendData[100];
        sprintf(sSendData, sTemSendData, creatSum(QString(sTemSendData)).c_str());

        QString strSendData = sSendData;//*/

        std::cout << strSendData.toStdString()<<'\n';

        (*itr)->write(strSendData.toLatin1().data(), strSendData.length());
        ++m_iSendDataNum;
      }
      else
      {
        m_iSendDataNum = 0;
      }
    }
  }
}

void uiSingleServerWidget::readDataFromTxt()
{
  m_sAddress = ui.lineEdit_Address->text().toStdString();

  FILE* pFileData;
  pFileData = fopen(m_sAddress.c_str(), "r");
  if (!pFileData)
    return;

  char cWord = 0;
  while (cWord != EOF)
  {
    cWord = getc(pFileData);
    m_sSendDataGroup += cWord;
  }

  fclose(pFileData);
}

void uiSingleServerWidget::writeConfig()
{
  g_Settings.beginGroup(QString("Server") + QString::number(m_iWidgetID, 10));

  g_Settings.setValue("Port", ui.spinBox_Port->value());
  g_Settings.setValue("Timeout", ui.spinBox_Timeout->value());
  g_Settings.setValue("Enable", ui.checkBox->isChecked() ? "True" : "False");
  g_Settings.setValue("Address", ui.lineEdit_Address->text());

  g_Settings.endGroup();
}

void uiSingleServerWidget::closeSocket()
{
  for (pSocketItr itr = m_vSocketGroup.begin(); itr != m_vSocketGroup.end(); )
  {
    if ((*itr)->isOpen())
    {
      (*itr)->close();
      if (m_vSocketGroup.size() == 0)
        break;
      continue;
    }
    ++itr;
  }
}

void uiSingleServerWidget::slotNewClient()
{
  QTcpSocket* pSocketTem = m_pTcpServer->nextPendingConnection();
  m_vSocketGroup.push_back(pSocketTem);
  /*异步执行，同步执行时在超时关闭的时，关闭socket调用slotDisconnection，erase了socket对象改变m_vSocketGroup回到closeSocket执行之后的代码，迭代器在
  判断itr != m_vSocketGroup.end()时会崩溃*/
  connect(pSocketTem, &QTcpSocket::disconnected, this, &uiSingleServerWidget::slotDisconnection, Qt::ConnectionType::QueuedConnection);
  connect(pSocketTem, &QTcpSocket::disconnected, pSocketTem, &QTcpSocket::deleteLater);
}

void uiSingleServerWidget::slotDisconnection()
{
  QTcpSocket* pSocketTem = qobject_cast<QTcpSocket*>(sender());
  for (pSocketItr itr = m_vSocketGroup.begin(); itr != m_vSocketGroup.end(); ++itr)
  {
    if ((*itr) == pSocketTem)
    {
      itr = m_vSocketGroup.erase(itr);
      break;
    }
  }
}
