#include "TcpServer.h"

jyTcpServer::jyTcpServer()
{
  ui.setupUi(this);
//  readConfigFile();
  initWidget();
  //writeFile();
}

void jyTcpServer::writeFile()
{
  QFile _temFile1("C://Users//Administrator//Desktop//GPGGA1001.txt");
  if (!_temFile1.open(QIODevice::ReadWrite))
  {

  }
  else
  {
    QString GPGGADATA = "[1001] $GPGGA,121252.001,3936.3032,N,11610.6046,E,1,05,2.0,45.9,M,-5.7,M,,0000*77";
    QStringList tem = GPGGADATA.split(",");
    for (int i = 0; i < 1000; ++i)
    {
      
      double temdouble = tem[1].toDouble();
      temdouble = temdouble + 0.200;
      tem[1] = QString::number(temdouble,'f',4);
      tem[2] = QString::number(tem[2].toDouble() - 0.0008,'f',4);
      tem[4] = QString::number(tem[4].toDouble(),'f',4);
      qDebug() << fixed << qSetRealNumberPrecision(7) << temdouble;
      qint64 pos;
      pos = _temFile1.size();
      _temFile1.seek(pos);
      QString temqstring = "";
      for (int i = 0; i < tem.length(); ++i)
      {
        temqstring.append(tem[i]+",");
      }
      temqstring.chop(1);
      temqstring.append("|");
      _temFile1.write(temqstring.toLatin1(), temqstring.length());
    }
    }
  QFile _temFile2("C://Users//Administrator//Desktop//GPGGA1002.txt");
  if (!_temFile2.open(QIODevice::ReadWrite))
  {

  }
  else
  {
    QString GPGGADATA2 = "[1002] $GPGGA,121252.001,3936.3032,N,11610.6146,E,1,05,2.0,45.9,M,-5.7,M,,0000*77";
    QStringList tem = GPGGADATA2.split(",");
    for (int i = 0; i < 1000; ++i)
    {

      double temdouble = tem[1].toDouble();
      temdouble = temdouble + 0.200;
      tem[1] = QString::number(temdouble, 'f', 4);
      tem[2] = QString::number(tem[2].toDouble() - 0.0008, 'f', 4);
      tem[4] = QString::number(tem[4].toDouble(), 'f', 4);
      qDebug() << fixed << qSetRealNumberPrecision(7) << temdouble;
      qint64 pos;
      pos = _temFile2.size();
      _temFile2.seek(pos);
      QString temqstring = "";
      for (int i = 0; i < tem.length(); ++i)
      {
        temqstring.append(tem[i] + ",");
      }
      temqstring.chop(1);
      temqstring.append("|");
      _temFile2.write(temqstring.toLatin1(), temqstring.length());
    }
  }
  QFile _temFile3("C://Users//Administrator//Desktop//GPGGA1003.txt");
  if (!_temFile3.open(QIODevice::ReadWrite))
  {

  }
  else
  {
    QString GPGGADATA3 = "[1003] $GPGGA,121252.001,3936.3032,N,11610.6046,E,1,05,2.0,45.9,M,-5.7,M,,0000*77";
    QStringList tem3 = GPGGADATA3.split(",");
    for (int i = 0; i < 2000; ++i)
    {

      double temdouble = tem3[1].toDouble();
      temdouble = temdouble + 0.200;
      tem3[1] = QString::number(temdouble, 'f', 4);
      tem3[2] = QString::number(tem3[2].toDouble() + 0.0002, 'f', 4);
      tem3[4] = QString::number(tem3[4].toDouble() , 'f', 4);
      qDebug() << fixed << qSetRealNumberPrecision(7) << temdouble;
      qint64 pos;
      pos = _temFile3.size();
      _temFile3.seek(pos);
      QString temqstring = "";
      for (int i = 0; i < tem3.length(); ++i)
      {
        temqstring.append(tem3[i] + ",");
      }
      temqstring.chop(1);
      temqstring.append("|");
      _temFile3.write(temqstring.toLatin1(), temqstring.length());
    }
  }
  QFile _temFile4("C://Users//Administrator//Desktop//GPGGA1004.txt");
  if (!_temFile4.open(QIODevice::ReadWrite))
  {

  }
  else
  {
    QString GPGGADATA4 = "[1004] $GPGGA,121252.001,3936.3032,N,11610.6146,E,1,05,2.0,45.9,M,-5.7,M,,0000*77";
    QStringList tem = GPGGADATA4.split(",");
    for (int i = 0; i < 2000; ++i)
    {

      double temdouble = tem[1].toDouble();
      temdouble = temdouble + 0.200;
      tem[1] = QString::number(temdouble, 'f', 4);
      tem[2] = QString::number(tem[2].toDouble() + 0.0002, 'f', 4);
      tem[4] = QString::number(tem[4].toDouble() , 'f', 4);
      qDebug() << fixed << qSetRealNumberPrecision(7) << temdouble;
      qint64 pos;
      pos = _temFile1.size();
      _temFile1.seek(pos);
      QString temqstring = "";
      for (int i = 0; i < tem.length(); ++i)
      {
        temqstring.append(tem[i] + ",");
      }
      temqstring.chop(1);
      temqstring.append("|");
      _temFile4.write(temqstring.toLatin1(), temqstring.length());
    }
  }

    
}
void jyTcpServer::readConfigFile()
{
  g_Settings.beginGroup("Main");
  int _iflag = g_Settings.value("ServerNum").toInt();
  int _serverNum = (g_Settings.allKeys().length() - 1) / 3;
  g_Settings.endGroup();
  if (_serverNum >= _iflag && g_Settings.contains("Main/ServerNum"))
  {
    g_Settings.beginGroup("Main");
    m_iServerNum = g_Settings.value("ServerNum").toInt();
    g_Settings.endGroup();
  }
  else
  {
    g_Settings.beginGroup("Main");
    g_Settings.setValue("ServerNum", m_iServerNum);
    g_Settings.endGroup();
    for (int i = 0; i < m_iServerNum; ++i)
    {
      QString _temKey = QString("Server") + QString::number(i, 10);
      g_Settings.beginGroup(_temKey);
      g_Settings.setValue("Port", m_iPort);
      g_Settings.setValue("Time", m_iTime);
      g_Settings.setValue("Address", m_sAddress);
      g_Settings.endGroup();
    }
  }

}
void jyTcpServer::initWidget()
{
  g_Settings.beginGroup("Main");
  if (g_Settings.value("ServerNum").isNull())
    g_Settings.setValue("ServerNum", 4);
  m_iServerNum = g_Settings.value("ServerNum").toInt();
  g_Settings.endGroup();
  for (int i = 0; i < m_iServerNum; ++i)
  {
    m_vServerWidgetGroup.append(new uiSingleServerWidget(i, this));
    m_vServerWidgetGroup[i]->initData();
    ui.verticalLayout->addWidget(m_vServerWidgetGroup[i]);
  }
}
/*
void jyTcpServer::initData(int iPort, int iTime, const QString & sAddress)
{
  QSettings _settings("TcpServerConfig.ini", QSettings::IniFormat);
  if (_settings.contains("TcpServer/Port"))
  {
    ui.widgetui->spinBox_port->setValue(_settings.value("TcpServer/Port").toInt());
    ui.spinBox_Timeout->setValue(_settings.value("TcpServer/Time").toInt());
    ui.lineEdit_FileAddr->setText(_settings.value("TcpServer/FileAddress").toString());
  }
  else
  {
    _settings.beginGroup("TcpServer");
    _settings.setValue("Port", iPort);
    _settings.setValue("Time", iTime);
    _settings.setValue("FileAddress", sAddress);
    _settings.endGroup();
  }
}*/






