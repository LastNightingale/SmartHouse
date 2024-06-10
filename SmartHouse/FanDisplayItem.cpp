// Fill out your copyright notice in the Description page of Project Settings.


#include "FanDisplayItem.h"
#include "Components/Button.h"

void UFanDisplayItem::OnTurnOnClick()
{
	SendCommand(DeviceIP, FName(TEXT("TurnOn")));
}

void UFanDisplayItem::OnTurnOffClick()
{
	SendCommand(DeviceIP, FName(TEXT("TurnOff")));
}

void UFanDisplayItem::OnSetSpeedOneClick()
{
	SendCommand(DeviceIP, FName(TEXT("SetSpeedOne")));
}

void UFanDisplayItem::OnSetSpeedTwoClick()
{
	SendCommand(DeviceIP, FName(TEXT("SetSpeedTwo")));
}

void UFanDisplayItem::NativeConstruct()
{
	Super::NativeConstruct();

	TurnOnButton->OnClicked.AddDynamic(this, &UFanDisplayItem::OnTurnOnClick);
	TurnOffButton->OnClicked.AddDynamic(this, &UFanDisplayItem::OnTurnOffClick);
	SetSpeedOneButton->OnClicked.AddDynamic(this, &UFanDisplayItem::OnSetSpeedOneClick);
	SetSpeedTwoButton->OnClicked.AddDynamic(this, &UFanDisplayItem::OnSetSpeedTwoClick);
}
