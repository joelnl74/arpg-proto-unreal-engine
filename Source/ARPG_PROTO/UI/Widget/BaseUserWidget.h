

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_PROTO_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* NewWidgetController);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void HandleSetWidgetController();
	
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> widgetController;
};
