

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerGameplayAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class ARPG_PROTO_API UPlayerGameplayAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPlayerGameplayAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& attribute, float& newValue) override;

	UFUNCTION()
	void onRep_Health(const FGameplayAttributeData &oldHealth);

	UFUNCTION()
	void onRep_MaxHealth(const FGameplayAttributeData &oldMaxHealth);

	UFUNCTION()
	void onRep_Mana(const FGameplayAttributeData& oldMana);

	UFUNCTION()
	void onRep_MaxMana(const FGameplayAttributeData &oldMaxMana);

public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = onRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData health;
	ATTRIBUTE_ACCESSORS(UPlayerGameplayAttributeSet, health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = onRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData maxHealth;
	ATTRIBUTE_ACCESSORS(UPlayerGameplayAttributeSet, maxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = onRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData mana;
	ATTRIBUTE_ACCESSORS(UPlayerGameplayAttributeSet, mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = onRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData maxMana;
	ATTRIBUTE_ACCESSORS(UPlayerGameplayAttributeSet, maxMana);

};
