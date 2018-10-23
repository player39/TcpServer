#include "uiTestDataCreatWidget.h"

#define LNG_LAT_DIFFERENCE 0.0008

uiTestDataCreatWidget::uiTestDataCreatWidget(QWidget* parent /* = Q_NULLPTR*/ )
{
  ui.setupUi(this);

  m_sTestData = "[%d] $GPGGA,%%s,%f,N,%f,E,1,06,9.9,35.986,M,0.00,M,,*%%s|";

  connect(ui.pushButton_creatData, &QPushButton::clicked, this, &uiTestDataCreatWidget::creatData);
}

void uiTestDataCreatWidget::creatData()
{
  QString strDataGroup = "";
  QStringList strlCenterCoordinate = ui.lineEdit_CenterCoordinate->text().split(',');
  double dLat = strlCenterCoordinate[0].toDouble();
  double dLng = strlCenterCoordinate[1].toDouble();
  QString strGPSID = ui.lineEdit_GPSID->text();
  QString strFileName = QString("GPGGA") + strGPSID;
  int iDataAmount = ui.lineEdit_DataAmount->text().toInt();

  FILE* pFileData;
  pFileData = fopen(strFileName.toStdString().c_str(), "w");
  for (int i = 0; i < iDataAmount; ++i)
  {
    fprintf(pFileData, m_sTestData.c_str(), strGPSID.toInt(), dLat, dLng);
    dLat += LNG_LAT_DIFFERENCE;
  }

  fclose(pFileData);
}
