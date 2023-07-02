
#include "ARPG_PROTO/Actor/ARPGEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "ARPG_PROTO/AbilitySystem/PlayerGameplayAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AARPGEffectActor::AARPGEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(mesh);

	sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	sphere->SetupAttachment(GetRootComponent());

}

void AARPGEffectActor::OnOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(otherActor))
	{
		const UPlayerGameplayAttributeSet* attributeSet = Cast<UPlayerGameplayAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UPlayerGameplayAttributeSet::StaticClass()));

		UPlayerGameplayAttributeSet* mutableAuraAttributeSet = const_cast<UPlayerGameplayAttributeSet*>(attributeSet);
		mutableAuraAttributeSet->Sethealth(attributeSet->Gethealth() + 25.f);
		mutableAuraAttributeSet->Setmana(attributeSet->Getmana() - 25.f);
		Destroy();
	}
}

void AARPGEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called when the game starts or when spawned
void AARPGEffectActor::BeginPlay()
{
	Super::BeginPlay();

	sphere->OnComponentBeginOverlap.AddDynamic(this, &AARPGEffectActor::OnOverlap);
	sphere->OnComponentEndOverlap.AddDynamic(this, &AARPGEffectActor::EndOverlap);
	
}

