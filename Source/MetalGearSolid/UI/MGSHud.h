// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MGSHud.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARSOLID_API AMGSHud : public AHUD
{
	GENERATED_BODY()

public:
	AMGSHud();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	UPROPERTY(EditDefaultsOnly, Category= Widgets)
	TSubclassOf<UUserWidget> HudUserWidgetClass;

	void ShowWeaponSelection() const;
	void HideWeaponSelection() const;

	void WeaponSelectionIndex(int X) const;

private:
	UPROPERTY()
	class UMGSHUDUserWidget* HudWidget;
};
