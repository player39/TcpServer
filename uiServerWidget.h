
#ifndef _SERVERWIDGET_H
#define _SERVERWIDGET_H

#include <QtWidgets/QWidget>
#include "ui_uiServerWidget.h"
#include "ui_uiTestDataCreatWidget.h"
#include <QtCore/QSettings>

class uiServerWidget : public QWidget
{
public:
  uiServerWidget(QWidget* parent = Q_NULLPTR);
  ~uiServerWidget();

private:
  Ui::uiServerWidget ui;
};

#endif  // _SERVERWIDGET_H
