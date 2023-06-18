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
};
