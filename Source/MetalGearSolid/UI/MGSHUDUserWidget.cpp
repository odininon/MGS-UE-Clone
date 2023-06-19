// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSHUDUserWidget.h"

#include "MGSItemWidget.h"
#include "MGSUtilitySelectionWidget.h"
#include "MGSWeaponSelectionWidget.h"
#include "MetalGearSolid/MGSInventoryComponent.h"
#include "MetalGearSolid/Items/MGSWeaponItem.h"

UMGSHUDUserWidget::UMGSHUDUserWidget(const FObjectInitializer& ObjectInitializer): UUserWidget(ObjectInitializer)
{
}

void UMGSHUDUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (WeaponSelection)
	{
		WeaponSelection->SetVisibility(ESlateVisibility::Hidden);
	}

	if (UtilitySelection)
	{
		UtilitySelection->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMGSHUDUserWidget::SetInventory(UMGSInventoryComponent* p_InventoryComponent)
{
	this->InventoryComponent = p_InventoryComponent;
}

void UMGSHUDUserWidget::ShowWeaponSelection()
{
	if (UtilitySelection)
	{
		UtilitySelection->SetVisibility(ESlateVisibility::Hidden);
	}

	if (SelectedUtility)
	{
		SelectedUtility->SetVisibility(ESlateVisibility::Hidden);
	}

	if (SelectedWeapon)
	{
		SelectedWeapon->SetVisibility(ESlateVisibility::Hidden);
	}

	if (WeaponSelection)
	{
		WeaponSelection->SetVisibility(ESlateVisibility::Visible);
		WeaponSelection->SetItems(this->InventoryComponent->WeaponItems);
		WeaponSelection->BeginSelection();
	}
}

void UMGSHUDUserWidget::HideWeaponSelection()
{
	if (WeaponSelection)
	{
		WeaponSelection->SetVisibility(ESlateVisibility::Hidden);
		WeaponSelection->EndSelection();

		const auto SelectedWeaponIndex = WeaponSelection->SelectedIndex;

		if (SelectedWeapon && InventoryComponent->WeaponItems.Num() > 0)
		{
			SelectedWeapon->SetItem(InventoryComponent->WeaponItems[SelectedWeaponIndex]);
			SelectedWeapon->SetVisibility(ESlateVisibility::Visible);
		}
	}

	if (SelectedUtility)
	{
		SelectedUtility->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMGSHUDUserWidget::WeaponSelectionIndex(int X)
{
	if (WeaponSelection)
	{
		WeaponSelection->AddIndex(X);
	}
}
