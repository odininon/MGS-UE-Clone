// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSItemWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MetalGearSolid/Items/MGSItem.h"

void UMGSItemWidget::SetItem(UMGSItem* p_Item)
{
	this->Item = p_Item;

	NameText->SetText(Item->ItemDisplayName);

	//TODO: Figure out how to set Thumbnails from Texture2D
	// ThumbnailImage->SetBrush(Item->Thumbnail);
}
