
#include "uiServerWidget.h"
#include "uiSingleServerWidget.h"
#include "uiTestDataCreatWidget.h"
#include "Config.h"

#define STR_MAIN_SERVERCOUNT "/Main/ServerCount"

uiServerWidget::uiServerWidget(QWidget* parent /* = Q_NULLPTR */)
  : QWidget(parent)
{
  ui.setupUi(this);

  if (g_Settings.value(STR_MAIN_SERVERCOUNT).isNull())
    g_Settings.setValue(STR_MAIN_SERVERCOUNT, 6);
  int iCount = g_Settings.value(STR_MAIN_SERVERCOUNT).toInt();
  uiTestDataCreatWidget* pTestDataCreatWidget = new uiTestDataCreatWidget(this);
  ui.verticalLayout_2->addWidget(pTestDataCreatWidget);
  for (int i = 0; i < iCount; ++i)
  {
    uiSingleServerWidget* pSingleServerWidget = new uiSingleServerWidget(this);
    pSingleServerWidget->initWidget(i + 1);
    ui.verticalLayout_2->addWidget(pSingleServerWidget);
  }
}

uiServerWidget::~uiServerWidget()
{
}
