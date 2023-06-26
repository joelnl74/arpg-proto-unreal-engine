#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGEffectActor.generated.h"

class USphereComponent;

UCLASS()
class ARPG_PROTO_API AARPGEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARPGEffectActor();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex);
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> mesh;

};
