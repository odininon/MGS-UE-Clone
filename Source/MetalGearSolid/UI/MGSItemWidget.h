// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGSItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARSOLID_API UMGSItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta= (BindWidget))
	class UImage* ThumbnailImage;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta= (BindWidget))
	class UTextBlock* NameText;
	
	void SetItem(class UMGSItem* p_Item);

	UPROPERTY()
	class UMGSItem* Item;
};
