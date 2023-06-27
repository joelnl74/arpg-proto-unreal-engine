


#include "ARPG_PROTO/UI/Widget/BaseUserWidget.h"

void UBaseUserWidget::SetWidgetController(UObject* NewWidgetController)
{
	widgetController = NewWidgetController;
	HandleSetWidgetController();
}
