// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGSHUDUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARSOLID_API UMGSHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMGSHUDUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;


	UPROPERTY(EditDefaultsOnly, Meta = (BindWidget))
	class UMGSWeaponSelectionWidget* WeaponSelection;

	void ShowWeaponSelection();
	void HideWeaponSelection();
	void WeaponSelectionIndex(int X);
};
