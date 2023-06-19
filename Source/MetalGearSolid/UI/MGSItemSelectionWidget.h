// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGSItemSelectionWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class METALGEARSOLID_API UMGSItemSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Selection)
	int SelectedIndex = 0;
	
	virtual void SelectNextIndex();
	virtual void SelectPreviousIndex();

	virtual void BeginSelection();
	virtual void EndSelection();
	virtual void AddIndex(int X);
};
