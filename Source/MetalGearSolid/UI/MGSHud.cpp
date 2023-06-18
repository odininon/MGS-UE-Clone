// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSHud.h"

#include "MGSHUDUserWidget.h"
#include "Blueprint/UserWidget.h"

AMGSHud::AMGSHud()
{
}

void AMGSHud::DrawHUD()
{
	Super::DrawHUD();
}

void AMGSHud::BeginPlay()
{
	Super::BeginPlay();

	if (HudUserWidgetClass)
	{
		HudWidget = CreateWidget<UMGSHUDUserWidget>(GetWorld(), HudUserWidgetClass);

		if (HudWidget)
		{
			HudWidget->AddToViewport();
		}
	}
}

void AMGSHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMGSHud::ShowWeaponSelection() const
{
	if (HudWidget)
	{
		HudWidget->ShowWeaponSelection();
	}
}

void AMGSHud::HideWeaponSelection() const
{
	if (HudWidget)
	{
		HudWidget->HideWeaponSelection();
	}
}

void AMGSHud::WeaponSelectionIndex(int X) const
{
	if (HudWidget)
	{
		HudWidget->WeaponSelectionIndex(X);
	}
}
