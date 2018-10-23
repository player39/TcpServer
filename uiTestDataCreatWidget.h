
#ifndef _UITESTDATACREATWIDGET_H
#define _UITESTDATACREATWIDGET_H

#include <QtWidgets/QWidget>
#include "ui_uiTestDataCreatWidget.h"

class uiTestDataCreatWidget :public QWidget
{

  Q_OBJECT

public:
  uiTestDataCreatWidget(QWidget* parent = Q_NULLPTR);
  void creatData();
private:
  std::string m_sTestData;
  Ui::uiTestDataCreatWidget ui;
  
};

#endif  //_UITESTDATACREATWIDGET_H