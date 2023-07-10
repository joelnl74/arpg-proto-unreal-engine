#include "ARPG_PROTO/AbilitySystem/PlayerGameplayAttributeSet.h"
#include "Net/UnrealNetwork.h"

UPlayerGameplayAttributeSet::UPlayerGameplayAttributeSet()
{
	Inithealth(50.f);
	InitmaxHealth(100.f);
	Initmana(10.0f);
	InitmaxMana(50.f);
}

void UPlayerGameplayAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerGameplayAttributeSet, health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerGameplayAttributeSet, maxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerGameplayAttributeSet, mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerGameplayAttributeSet, maxMana, COND_None, REPNOTIFY_Always);
}

void UPlayerGameplayAttributeSet::PreAttributeChange(const FGameplayAttribute& attribute, float& newValue)
{
	Super::PreAttributeChange(attribute, newValue);

	if (attribute == GethealthAttribute())
	{
		newValue = FMath::Clamp(newValue, 0.f, GetmaxHealth());
	}
	if (attribute == GetmanaAttribute())
	{
		newValue = FMath::Clamp(newValue, 0.f, GetmaxMana());
	}
}

void UPlayerGameplayAttributeSet::onRep_Health(const FGameplayAttributeData& oldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerGameplayAttributeSet, health, oldHealth);
}

void UPlayerGameplayAttributeSet::onRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerGameplayAttributeSet, maxHealth, oldMaxHealth);

}

void UPlayerGameplayAttributeSet::onRep_Mana(const FGameplayAttributeData& oldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerGameplayAttributeSet, mana, oldMana);
}

void UPlayerGameplayAttributeSet::onRep_MaxMana(const FGameplayAttributeData& oldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerGameplayAttributeSet, maxMana, oldMaxMana);
}
