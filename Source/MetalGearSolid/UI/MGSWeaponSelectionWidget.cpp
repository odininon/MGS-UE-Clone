// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSWeaponSelectionWidget.h"

#include "Components/TextBlock.h"

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

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Showing Weapon Selection"));
	}
}

void UMGSWeaponSelectionWidget::EndSelection()
{
	Super::EndSelection();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Hiding Weapon Selection"));
	}
}

void UMGSWeaponSelectionWidget::AddIndex(int X)
{
	Super::AddIndex(X);

	SelectedIndex += X;
	SelectedIndexText->SetText(FText::FromString(FString::Printf(TEXT("%d"), SelectedIndex)));
}
