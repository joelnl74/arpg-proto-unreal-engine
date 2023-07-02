#pragma once

#include "CoreMinimal.h"
#include "ARPG_PROTO/UI/WidgetController/BaseWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, newHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, newMaxHealth);

UCLASS(BlueprintType, Blueprintable)
class ARPG_PROTO_API UOverlayWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadCastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

public:
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangedSignature onHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChangedSignature onMaxHealthChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& data) const;
};
