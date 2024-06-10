// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TabletWidget.h"
#include "DeviceDisplayWidget.h"
#include "ConfigConnectableWidget.h"
#include "Gateway.h"

#include "SmartHousePlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class SMARTHOUSE_API ASmartHousePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTabletWidget> TabletWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UDeviceDisplayWidget> DeviceDisplayWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UConfigConnectableWidget> ConfigWidgetClass;

	UPROPERTY()
	UDeviceDisplayWidget* DeviceDisplayWidget;

	UPROPERTY()
	UConfigConnectableWidget* ConfigWidget;

	UPROPERTY()
	AGateway* ConnectedGateway = nullptr;


	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface

public:	

	UPROPERTY()
	AConnectableTablet* ConnectedTablet;

	UPROPERTY()
	UTabletWidget* TabletUI;

	UPROPERTY()
	UDeviceDisplayWidget* DDWUI;

	void UpdateDevices(AGateway* Gateway);

	void UpdateConfig(AConnectable* Connectable);

	void ShowTablet();

	void ShowConfig();

	void ClearDevices();

	AGateway* GetGateway() { return ConnectedGateway; };
};
