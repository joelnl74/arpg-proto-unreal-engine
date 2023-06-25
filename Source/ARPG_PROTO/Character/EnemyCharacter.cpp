#include "ARPG_PROTO/Character/EnemyCharacter.h"

#include "ARPG_PROTO/AbilitySystem/PlayerAbilitySystemComponent.h"
#include "ARPG_PROTO/AbilitySystem/PlayerGameplayAttributeSet.h"
#include <ARPG_PROTO/ARPG_PROTO.h>



void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	abilitySystemComponent->InitAbilityActorInfo(this, this);
}

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	abilitySystemComponent = CreateDefaultSubobject<UPlayerAbilitySystemComponent>("AbilitySystemComponent");
	abilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	abilitySystemComponent->SetIsReplicated(true);

	attributeSet = CreateDefaultSubobject<UPlayerGameplayAttributeSet>("AttributeSet");
}

void AEnemyCharacter::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	weaponSlot->SetRenderCustomDepth(true);
	weaponSlot->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AEnemyCharacter::UnHighLightActor()
{
	weaponSlot->SetRenderCustomDepth(false);
	GetMesh()->SetRenderCustomDepth(false);
}
