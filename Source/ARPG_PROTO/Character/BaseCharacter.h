#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(abstract)
class ARPG_PROTO_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<USkeletalMeshComponent> weaponSlot;
};
