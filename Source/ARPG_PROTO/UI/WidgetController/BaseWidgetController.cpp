#include "ARPG_PROTO/UI/WidgetController/BaseWidgetController.h"

void UBaseWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	playerController = WCParams.playerController;
	playerState = WCParams.playerState;
	abilitySystemComponent = WCParams.abilitySystemComponent;
	attributeSet = WCParams.attributeSet;
}

void UBaseWidgetController::BroadCastInitialValues() {}
void UBaseWidgetController::BindCallbacksToDependencies() {}
