#include "ARPG_PROTO/UI/HUD/GameUIHUD.h"

#include "ARPG_PROTO/UI/Widget/BaseUserWidget.h"
#include "ARPG_PROTO/UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AGameUIHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (overlayWidgetController == nullptr)
	{
		overlayWidgetController = NewObject<UOverlayWidgetController>(this, overlayWidgetControllerClass);
		overlayWidgetController->SetWidgetControllerParams(WCParams);

		return overlayWidgetController;
	}

	return overlayWidgetController;
}

void AGameUIHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(overlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(overlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), overlayWidgetClass);
	overlayWidget = Cast<UBaseUserWidget>(widget);

	const FWidgetControllerParams widgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* widgetController = GetOverlayWidgetController(widgetControllerParams);

	overlayWidget->SetWidgetController(widgetController);

	widget->AddToViewport();
}
