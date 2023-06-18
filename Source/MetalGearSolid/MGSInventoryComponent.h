// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MGSInventoryComponent.generated.h"


DECLARE_DYNAMIC_DELEGATE(FOnInventoryUpdated);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class METALGEARSOLID_API UMGSInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMGSInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	bool AddItem(class UMGSItem* Item);
	bool RemoveItem(class UMGSItem* Item);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Items)
	TArray<class UMGSUtilityItem*> UtilityItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Items)
	TArray<class UMGSWeaponItem*> WeaponItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Items)
	class UMGSUtilityItem* CurrentlyEquippedUtility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Items)
	class UMGSWeaponItem* CurrentlyEquippedWeapon;
};
