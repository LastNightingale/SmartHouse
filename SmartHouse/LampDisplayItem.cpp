// Fill out your copyright notice in the Description page of Project Settings.


#include "LampDisplayItem.h"
#include "Components/Button.h"

void ULampDisplayItem::OnTurnOnClick()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *DeviceIP.ToString());
	SendCommand(DeviceIP, FName(TEXT("TurnOn")));
}

void ULampDisplayItem::OnTurnOffClick()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OFFED"));
	SendCommand(DeviceIP, FName("TurnOff"));
}

void ULampDisplayItem::NativeConstruct()
{
	Super::NativeConstruct();

	TurnOnButton->OnClicked.AddDynamic(this, &ULampDisplayItem::OnTurnOnClick);
	TurnOffButton->OnClicked.AddDynamic(this, &ULampDisplayItem::OnTurnOffClick);
}
