// Fill out your copyright notice in the Description page of Project Settings.


#include "TabletWidget.h"
#include "Components/TextBlock.h"

void UTabletWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TextConnected->SetText(FText::FromString("NotConnected"));
}

void UTabletWidget::SetText(FText text)
{
	TextConnected->SetText(text);
}
