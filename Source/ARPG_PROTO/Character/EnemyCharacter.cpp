#include "ARPG_PROTO/Character/EnemyCharacter.h"
#include <ARPG_PROTO/ARPG_PROTO.h>

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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
