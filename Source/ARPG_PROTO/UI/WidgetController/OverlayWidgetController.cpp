#include "ARPG_PROTO/UI/WidgetController/OverlayWidgetController.h"
#include "ARPG_PROTO/AbilitySystem/PlayerGameplayAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValues()
{
	const UPlayerGameplayAttributeSet* playerAttributeSet = CastChecked<UPlayerGameplayAttributeSet>(attributeSet);

	onHealthChanged.Broadcast(playerAttributeSet->Gethealth());
	onMaxHealthChanged.Broadcast(playerAttributeSet->GetmaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UPlayerGameplayAttributeSet* playerAttributeSet = CastChecked<UPlayerGameplayAttributeSet>(attributeSet);

	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		playerAttributeSet->GethealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		playerAttributeSet->GetmaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& data) const
{
	onHealthChanged.Broadcast(data.NewValue);

}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& data) const
{
	onMaxHealthChanged.Broadcast(data.NewValue);
}
