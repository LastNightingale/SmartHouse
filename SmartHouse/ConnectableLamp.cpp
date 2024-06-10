// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectableLamp.h"
#include "Components/PointLightComponent.h"

void AConnectableLamp::TurnOn()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Lamp turned on"));
	Light->SetVisibility(true);
}

void AConnectableLamp::TurnOff()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Lamp turned off"));
	Light->SetVisibility(false);
}

void AConnectableLamp::BeginPlay()
{
	Super::BeginPlay();

	Light->SetVisibility(false);
}

AConnectableLamp::AConnectableLamp()
{
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));

	Light->SetupAttachment(RootComponent);
}

bool AConnectableLamp::CanBePlaced(FHitResult TraceHit, FVector& Location)
{
	if (TraceHit.Normal.Z < 0.9f)
		return false;
	
	Location = TraceHit.Location;
	return true;
}

FString AConnectableLamp::GetDocInfo()
{
	FString info = Super::GetDocInfo();

	info.Append(Color);
	info.Append(",");
	info.Append(FString::SanitizeFloat(Power));
	info.Append(",");
	info.Append(Material);
	info.Append(",");
	info.Append(FString::SanitizeFloat(Brightness));
	info.Append(",");
	info.Append(FString::SanitizeFloat(Price));

	return info;
}
