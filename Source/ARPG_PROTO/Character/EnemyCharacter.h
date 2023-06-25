#pragma once

#include "CoreMinimal.h"
#include "ARPG_PROTO/Interaction/EnemyInterface.h"
#include "ARPG_PROTO/Character/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_PROTO_API AEnemyCharacter : public ABaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	void HighLightActor() override;
	void UnHighLightActor() override;
};
