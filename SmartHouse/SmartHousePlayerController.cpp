// Copyright Epic Games, Inc. All Rights Reserved.


#include "SmartHousePlayerController.h"
#include "EnhancedInputSubsystems.h"

#include "Gateway.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void ASmartHousePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));


		if (!TabletUI)
		{
			if (!TabletWidgetClass)
				return;

			TabletUI = CreateWidget<UTabletWidget>(this, TabletWidgetClass);

			//TabletUI->AddToViewport();

			//SetShowMouseCursor(true);
			//UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, TabletUI);

		}


		if (!DeviceDisplayWidget) // test
		{
			if (!DeviceDisplayWidgetClass)
				return;

			DeviceDisplayWidget = CreateWidget<UDeviceDisplayWidget>(this, DeviceDisplayWidgetClass);

			//DeviceDisplayWidget->AddToViewport();

		}

		if (!ConfigWidget) // test
		{
			if (!ConfigWidgetClass)
				return;

			ConfigWidget = CreateWidget<UConfigConnectableWidget>(this, ConfigWidgetClass);

			//DeviceDisplayWidget->AddToViewport();

		}
	}
}

void ASmartHousePlayerController::UpdateDevices(AGateway* Gateway)
{
	this->ConnectedGateway = Gateway;
	DeviceDisplayWidget->UpdateInfo(Gateway->GatherDeviceInfo());
	DeviceDisplayWidget->UpdateGatewayInfo(Gateway->GetDHCP().GatewayIP, Gateway->GetDHCP().SubnetIP);
}

void ASmartHousePlayerController::UpdateConfig(AConnectable* Connectable)
{
	ConfigWidget->UpdateWidget(Connectable);
}

void ASmartHousePlayerController::ShowTablet()
{
	if (!DeviceDisplayWidget)
		return;

	DeviceDisplayWidget->AddToViewport();
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, DeviceDisplayWidget);
	this->bShowMouseCursor = true;
}

void ASmartHousePlayerController::ShowConfig()
{
	if (!ConfigWidget)
		return;

	ConfigWidget->AddToViewport();
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, ConfigWidget);
	this->bShowMouseCursor = true;
}

void ASmartHousePlayerController::ClearDevices()
{
	DeviceDisplayWidget->ClearInfo();
}
