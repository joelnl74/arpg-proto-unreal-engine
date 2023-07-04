
#include "ARPG_PROTO/Actor/ARPGEffectActor.h"
#include "ARPG_PROTO/AbilitySystem/PlayerGameplayAttributeSet.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AARPGEffectActor::AARPGEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void AARPGEffectActor::BeginPlay()
{
	Super::BeginPlay();	
}

void AARPGEffectActor::ApplyEffectToTarget(AActor* target, TSubclassOf<UGameplayEffect> gameplayEffectClass)
{
	UAbilitySystemComponent* targetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(target);
	if (targetASC == nullptr)
	{
		return;
	}

	check(gameplayEffectClass);
	FGameplayEffectContextHandle effectContextHandle = targetASC->MakeEffectContext();
	effectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle effectSpecHandle = targetASC->MakeOutgoingSpec(gameplayEffectClass, 1.f, effectContextHandle);
	targetASC->ApplyGameplayEffectSpecToSelf(*effectSpecHandle.Data.Get());
}

