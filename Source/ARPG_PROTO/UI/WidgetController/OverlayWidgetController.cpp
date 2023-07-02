#include "ARPG_PROTO/UI/WidgetController/OverlayWidgetController.h"
#include "ARPG_PROTO/AbilitySystem/PlayerGameplayAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValues()
{
	const UPlayerGameplayAttributeSet* playerAttributeSet = CastChecked<UPlayerGameplayAttributeSet>(attributeSet);

	onHealthChanged.Broadcast(playerAttributeSet->Gethealth());
	onMaxHealthChanged.Broadcast(playerAttributeSet->GetmaxHealth());

	onManaChanged.Broadcast(playerAttributeSet->Getmana());
	onMaxManaChanged.Broadcast(playerAttributeSet->GetmaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UPlayerGameplayAttributeSet* playerAttributeSet = CastChecked<UPlayerGameplayAttributeSet>(attributeSet);

	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		playerAttributeSet->GethealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		playerAttributeSet->GetmaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		playerAttributeSet->GetmanaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		playerAttributeSet->GetmaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& data) const
{
	onHealthChanged.Broadcast(data.NewValue);

}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& data) const
{
	onMaxHealthChanged.Broadcast(data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& data) const
{
	onManaChanged.Broadcast(data.NewValue);

}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& data) const
{
	onMaxManaChanged.Broadcast(data.NewValue);
}
