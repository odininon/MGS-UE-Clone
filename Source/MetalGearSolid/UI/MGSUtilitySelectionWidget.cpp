// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSUtilitySelectionWidget.h"

#include "Components/TextBlock.h"


void UMGSUtilitySelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SelectedIndexText->SetText(FText::FromString(FString::Printf(TEXT("%d"), SelectedIndex)));
}

void UMGSUtilitySelectionWidget::SelectNextIndex()
{
	Super::SelectNextIndex();
}

void UMGSUtilitySelectionWidget::SelectPreviousIndex()
{
	Super::SelectPreviousIndex();
}

void UMGSUtilitySelectionWidget::BeginSelection()
{
	Super::BeginSelection();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Showing Weapon Selection"));
	}
}

void UMGSUtilitySelectionWidget::EndSelection()
{
	Super::EndSelection();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Hiding Weapon Selection"));
	}
}

void UMGSUtilitySelectionWidget::AddIndex(int X)
{
	Super::AddIndex(X);

	SelectedIndex += X;
	SelectedIndexText->SetText(FText::FromString(FString::Printf(TEXT("%d"), SelectedIndex)));
}
