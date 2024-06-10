// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceDisplayItem.h"
#include "Components/TextBlock.h"
#include "SmartHousePlayerController.h"
#include <Kismet/GameplayStatics.h>

void UDeviceDisplayItem::SetName(FText name)
{
	Name->SetText(name);
}

void UDeviceDisplayItem::SetIP(FText ip)
{
	IP->SetText(ip);
}

void UDeviceDisplayItem::SetType(FText type)
{
	Type->SetText(type);
}

void UDeviceDisplayItem::SetDeviceIP(const Address& deviceIP)
{
	this->DeviceIP = deviceIP;
}

void UDeviceDisplayItem::SendCommand(const Address& deviceIP, FName CommandName)
{
	ASmartHousePlayerController* SPC = Cast<ASmartHousePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	//SPC->GetGateway()->DoAction(deviceIP, CommandName);
	SPC->ConnectedTablet->SendCommand(deviceIP, CommandName);
}
