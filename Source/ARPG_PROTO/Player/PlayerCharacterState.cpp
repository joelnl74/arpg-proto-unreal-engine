#include "ARPG_PROTO/Player/PlayerCharacterState.h"
#include "ARPG_PROTO/AbilitySystem/PlayerAbilitySystemComponent.h"
#include "ARPG_PROTO/AbilitySystem/PlayerGameplayAttributeSet.h"

APlayerCharacterState::APlayerCharacterState()
{
	abilitySystemComponent = CreateDefaultSubobject<UPlayerAbilitySystemComponent>("AbilitySystemComponent");
	abilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	abilitySystemComponent->SetIsReplicated(true);

	attributeSet = CreateDefaultSubobject<UPlayerGameplayAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100;
}

UAbilitySystemComponent* APlayerCharacterState::GetAbilitySystemComponent() const
{
	return abilitySystemComponent;
}
