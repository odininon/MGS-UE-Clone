// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGSItemSelectionWidget.h"
#include "MGSWeaponSelectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARSOLID_API UMGSWeaponSelectionWidget : public UMGSItemSelectionWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SelectNextIndex() override;
	virtual void SelectPreviousIndex() override;

	virtual void BeginSelection() override;
	virtual void EndSelection() override;
	void SetupItemsSlots();
	virtual void AddIndex(int X) override;

	TArray<class UMGSWeaponItem*> Items;
	virtual void SetItems(TArray<class UMGSWeaponItem*> p_Items);;

	UPROPERTY(EditDefaultsOnly, meta= (BindWidget))
	class UTextBlock* SelectedIndexText;

	UPROPERTY(EditDefaultsOnly, meta= (BindWidget))
	class UMGSItemWidget* Slot01;

	UPROPERTY(EditDefaultsOnly, meta= (BindWidget))
	class UMGSItemWidget* Slot02;
	
	UPROPERTY(EditDefaultsOnly, meta= (BindWidget))
	class UMGSItemWidget* Slot03;
	
	UPROPERTY(EditDefaultsOnly, meta= (BindWidget))
	class UMGSItemWidget* Slot04;
};
