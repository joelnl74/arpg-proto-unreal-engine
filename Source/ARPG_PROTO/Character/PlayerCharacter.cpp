#include "ARPG_PROTO/Character/PlayerCharacter.h"
#include "ARPG_PROTO/Player/PlayerCharacterState.h"
#include "ARPG_PROTO/Player/PlayerCharacterController.h"
#include "ARPG_PROTO/UI/HUD/GameUIHUD.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	APlayerCharacterState* playerCharacterState = GetPlayerState<APlayerCharacterState>();
	check(playerCharacterState);
	playerCharacterState->GetAbilitySystemComponent()->InitAbilityActorInfo(playerCharacterState, this);
	abilitySystemComponent = playerCharacterState->GetAbilitySystemComponent();
	attributeSet = playerCharacterState->GetAttributeSet();

	if (APlayerCharacterController* playerCharacterController = Cast<APlayerCharacterController>(GetController()))
	{
		if (AGameUIHUD* HUD = Cast<AGameUIHUD>(playerCharacterController->GetHUD()))
		{
			HUD->InitOverlay(playerCharacterController, playerCharacterState, abilitySystemComponent, attributeSet);
		}
	}
}
