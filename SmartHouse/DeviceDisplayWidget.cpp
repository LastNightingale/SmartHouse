// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceDisplayWidget.h"
#include "DeviceDisplayItem.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SmartHousePlayerController.h"
#include <Kismet/GameplayStatics.h>

void UDeviceDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton->OnClicked.AddDynamic(this, &UDeviceDisplayWidget::Exit);
	PrintButton->OnClicked.AddDynamic(this, &UDeviceDisplayWidget::Print);
}

void UDeviceDisplayWidget::UpdateInfo(TArray<DeviceInformation> DeviceInfo)
{
	DeviceDisplayScrollBox->ClearChildren();

	for (uint8 Iter = 0; Iter < DeviceInfo.Num(); ++Iter)
	{
		UDeviceDisplayItem* CurrentWidget = nullptr;/*
		if (DeviceInfo[Iter].DeviceType == EDeviceType::LAMP)
		{
			CurrentWidget = Cast<UDeviceDisplayItem>(CreateWidget(GetOwningPlayer(), WidgetTypes[DeviceInfo[Iter].DeviceType]));
		}
		else
			CurrentWidget = Cast<UDeviceDisplayItem>(CreateWidget(GetOwningPlayer(), ItemClass));*/
		if(!WidgetTypes.Contains(DeviceInfo[Iter].DeviceType))
			continue;

		/*CurrentWidget = Cast<UDeviceDisplayItem>(CreateWidget(GetOwningPlayer(), WidgetTypes.Contains(DeviceInfo[Iter].DeviceType) ?
			WidgetTypes[DeviceInfo[Iter].DeviceType] : ItemClass));*/
		CurrentWidget = Cast<UDeviceDisplayItem>(CreateWidget(GetOwningPlayer(), WidgetTypes[DeviceInfo[Iter].DeviceType]));
		CurrentWidget->SetName(DeviceInfo[Iter].Name);
		CurrentWidget->SetType(TypeNames.Contains(DeviceInfo[Iter].DeviceType) ? TypeNames[DeviceInfo[Iter].DeviceType]
			: FText::FromString("NULL"));
		CurrentWidget->SetIP(FText::FromString(DeviceInfo[Iter].IP.ToString()));
		CurrentWidget->SetDeviceIP(DeviceInfo[Iter].IP);
		DeviceDisplayScrollBox->AddChild(CurrentWidget);
	}
}

void UDeviceDisplayWidget::ClearInfo()
{
	DeviceDisplayScrollBox->ClearChildren();
}

void UDeviceDisplayWidget::Exit()
{
	this->RemoveFromViewport();
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
	PC->bShowMouseCursor = false;
}

void UDeviceDisplayWidget::Print()
{
	ASmartHousePlayerController* SPC = Cast<ASmartHousePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	SPC->ConnectedTablet->Print();
}

void UDeviceDisplayWidget::UpdateGatewayInfo(IPMask ipmask, Address address)
{
	SubnetIPText->SetText(FText::FromString(address.ToString()));
	GatewayIPText->SetText(FText::FromString(ipmask.IP.ToString()));
	GatewayMaskText->SetText(FText::FromString(ipmask.SubnetMask.ToString()));
}
