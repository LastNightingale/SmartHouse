// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectableTablet.h"
#include "SmartHousePlayerController.h"
#include "Kismet/GameplayStatics.h"

AConnectableTablet::AConnectableTablet()
{
	ConnectionType = EConnectionType::DHCP;
}

void AConnectableTablet::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TabletTimerHandle, this, &AConnectableTablet::UpdateDevices, 3.f, true);
}

void AConnectableTablet::UpdateDevices()
{
	ASmartHousePlayerController* PC = Cast<ASmartHousePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (!ConnectedGateway)
	{
		PC->ClearDevices();
	}
	else
	{
		PC->UpdateDevices(ConnectedGateway);
	}	
}

void AConnectableTablet::ShowTablet()
{
	ASmartHousePlayerController* PC = Cast<ASmartHousePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PC->ConnectedTablet = this;
	PC->ShowTablet();
}

void AConnectableTablet::Print()
{
	ConnectedGateway->WriteData();
}

void AConnectableTablet::SendCommand(const Address& deviceIP, FName CommandName)
{
	ConnectedGateway->DoAction(deviceIP, CommandName);
}
