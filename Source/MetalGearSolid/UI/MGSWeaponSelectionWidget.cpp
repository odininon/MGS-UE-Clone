// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSWeaponSelectionWidget.h"

#include "MGSItemWidget.h"
#include "Components/TextBlock.h"
#include "MetalGearSolid/Items/MGSWeaponItem.h"

void UMGSWeaponSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SelectedIndexText->SetText(FText::FromString(FString::Printf(TEXT("%d"), SelectedIndex)));
}

void UMGSWeaponSelectionWidget::SelectNextIndex()
{
	Super::SelectNextIndex();
}

void UMGSWeaponSelectionWidget::SelectPreviousIndex()
{
	Super::SelectPreviousIndex();
}

void UMGSWeaponSelectionWidget::BeginSelection()
{
	Super::BeginSelection();
}

void UMGSWeaponSelectionWidget::EndSelection()
{
	Super::EndSelection();
}

void UMGSWeaponSelectionWidget::SetupItemsSlots()
{
	if (Slot01)
	{
		Slot01->SetVisibility(ESlateVisibility::Hidden);
	}
	if (Slot02)
	{
		Slot02->SetVisibility(ESlateVisibility::Hidden);
	}
	if (Slot03)
	{
		Slot03->SetVisibility(ESlateVisibility::Hidden);
	}
	if (Slot04)
	{
		Slot04->SetVisibility(ESlateVisibility::Hidden);
	}

	const auto ItemCount = Items.Num();
	if (ItemCount >= 1)
	{
		Slot01->SetVisibility(ESlateVisibility::Visible);
		Slot01->SetItem(Items[SelectedIndex]);
	}

	if (ItemCount >= 2)
	{
		Slot02->SetVisibility(ESlateVisibility::Visible);
		Slot02->SetItem(Items[(SelectedIndex + ItemCount + 1) % ItemCount]);
	}

	if (ItemCount >= 3)
	{
		Slot03->SetVisibility(ESlateVisibility::Visible);
		Slot03->SetItem(Items[(SelectedIndex + ItemCount - 1) % ItemCount]);
	}

	if (ItemCount >= 4)
	{
		Slot04->SetVisibility(ESlateVisibility::Visible);
		Slot04->SetItem(Items[(SelectedIndex + ItemCount - 2) % ItemCount]);
	}
}

void UMGSWeaponSelectionWidget::AddIndex(int X)
{
	Super::AddIndex(X);

	if (Items.Num() != 0)
	{
		SelectedIndex = (SelectedIndex + X + Items.Num()) % Items.Num();
		SelectedIndexText->SetText(FText::FromString(FString::Printf(TEXT("%d"), SelectedIndex)));

		SetupItemsSlots();
	}
}

void UMGSWeaponSelectionWidget::SetItems(const TArray<UMGSWeaponItem*> p_Items)
{
	this->Items = p_Items;

	SetupItemsSlots();
}
