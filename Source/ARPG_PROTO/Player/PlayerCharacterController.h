#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"


// Forward declared.
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

 UCLASS()
class ARPG_PROTO_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerCharacterController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();

private:
	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<UInputMappingContext> inputMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> moveAction;

	IEnemyInterface* lastActor;
	IEnemyInterface* thisActor;
};
