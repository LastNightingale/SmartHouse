// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorDisplayItem.h"
#include "Components/Button.h"

void UDoorDisplayItem::OnLockClick()
{
	SendCommand(DeviceIP, FName(TEXT("Lock")));
}

void UDoorDisplayItem::OnUnlockClick()
{
	SendCommand(DeviceIP, FName(TEXT("Unlock")));
}

void UDoorDisplayItem::NativeConstruct()
{
	Super::NativeConstruct();

	LockButton->OnClicked.AddDynamic(this, &UDoorDisplayItem::OnLockClick);
	UnlockButton->OnClicked.AddDynamic(this, &UDoorDisplayItem::OnUnlockClick);
}
