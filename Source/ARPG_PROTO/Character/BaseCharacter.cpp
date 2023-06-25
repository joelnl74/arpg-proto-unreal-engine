#include "ARPG_PROTO/Character/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	weaponSlot = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponSlot");
	weaponSlot->SetupAttachment(GetMesh(), FName("WeaponSocketSlot"));
	weaponSlot->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
