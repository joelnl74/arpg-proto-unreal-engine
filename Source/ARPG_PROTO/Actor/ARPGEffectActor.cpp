
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
	const FActiveGameplayEffectHandle ActiveEffectHandle = targetASC->ApplyGameplayEffectSpecToSelf(*effectSpecHandle.Data.Get());

	const bool bIsInfinite = effectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && infiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		activeEffectHandles.Add(ActiveEffectHandle, targetASC);
	}

}

void AARPGEffectActor::OnOverlap(AActor* TargetActor)
{
	if (instantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, instantGameplayEffectClass);
	}
	if (durationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, durationGameplayEffectClass);
	}
	if (infiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, infiniteGameplayEffectClass);
	}
}

void AARPGEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (instantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, instantGameplayEffectClass);
	}
	if (durationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, durationGameplayEffectClass);
	}
	if (infiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* targetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(targetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : activeEffectHandles)
		{
			if (targetASC == HandlePair.Value)
			{
				targetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			activeEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}
