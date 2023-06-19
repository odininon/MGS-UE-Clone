// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGSItemSelectionWidget.h"
#include "MGSUtilitySelectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARSOLID_API UMGSUtilitySelectionWidget : public UMGSItemSelectionWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void SelectNextIndex() override;
	virtual void SelectPreviousIndex() override;

	virtual void BeginSelection() override;
	virtual void EndSelection() override;
	virtual void AddIndex(int X) override;

	UPROPERTY(EditDefaultsOnly, meta= (BindWidget))
	class UTextBlock* SelectedIndexText;
};
