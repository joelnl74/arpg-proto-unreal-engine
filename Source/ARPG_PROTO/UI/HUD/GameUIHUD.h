

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameUIHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UBaseUserWidget;
struct FWidgetControllerParams;

UCLASS()
class ARPG_PROTO_API AGameUIHUD : public AHUD
{
	GENERATED_BODY()


public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

public:
	UPROPERTY()
	TObjectPtr<UBaseUserWidget>  overlayWidget;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseUserWidget> overlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> overlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> overlayWidgetControllerClass;
};
