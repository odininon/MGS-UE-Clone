// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSInventoryComponent.h"

#include "Items/MGSUtilityItem.h"
#include "Items/MGSWeaponItem.h"

UMGSInventoryComponent::UMGSInventoryComponent()
{
}

void UMGSInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UMGSInventoryComponent::AddItem(UMGSItem* Item)
{
	if (UMGSWeaponItem* Weapon = Cast<UMGSWeaponItem>(Item))
	{
		if (WeaponItems.Contains(Weapon))
		{
			return false;
		}
		WeaponItems.Add(Weapon);
		return true;
	}

	if (UMGSUtilityItem* Utility = Cast<UMGSUtilityItem>(Item))
	{
		if (UtilityItems.Contains(Utility))
		{
			return false;
		}
		UtilityItems.Add(Utility);
		return true;
	}

	return false;
}

bool UMGSInventoryComponent::RemoveItem(UMGSItem* Item)
{
	return true;
}
