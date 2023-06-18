// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSHUDUserWidget.h"

#include "MGSWeaponSelectionWidget.h"

UMGSHUDUserWidget::UMGSHUDUserWidget(const FObjectInitializer& ObjectInitializer): UUserWidget(ObjectInitializer)
{
}

void UMGSHUDUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMGSHUDUserWidget::ShowWeaponSelection()
{
	if (WeaponSelection)
	{
		WeaponSelection->BeginSelection();
	}
}

void UMGSHUDUserWidget::HideWeaponSelection()
{
	if (WeaponSelection)
	{
		WeaponSelection->EndSelection();
	}
}

void UMGSHUDUserWidget::WeaponSelectionIndex(int X)
{
	if (WeaponSelection)
	{
		WeaponSelection->AddIndex(X);
	}
}
