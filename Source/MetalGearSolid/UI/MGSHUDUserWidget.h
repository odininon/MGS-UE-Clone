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
	void SetInventory(class UMGSInventoryComponent* p_InventoryComponent);

	UPROPERTY(EditDefaultsOnly, Meta = (BindWidget))
	class UMGSWeaponSelectionWidget* WeaponSelection;

	UPROPERTY(EditDefaultsOnly, Meta = (BindWidget))
	class UMGSItemWidget* SelectedWeapon;

	UPROPERTY(EditDefaultsOnly, Meta = (BindWidget))
	class UMGSUtilitySelectionWidget* UtilitySelection;

	UPROPERTY(EditDefaultsOnly, Meta = (BindWidget))
	class UMGSItemWidget* SelectedUtility;

	void ShowWeaponSelection();
	void HideWeaponSelection();
	void WeaponSelectionIndex(int X);

	UPROPERTY()
	class UMGSInventoryComponent* InventoryComponent;
};
