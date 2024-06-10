// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectableFan.h"
#include "GameFramework/RotatingMovementComponent.h"

AConnectableFan::AConnectableFan()
{
	Fan = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fan"));
	CoverTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoverTop"));
	CoverBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoverBottom"));
	Rotating = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating"));

	CoverBottom->AttachToComponent(CoverTop, FAttachmentTransformRules::KeepRelativeTransform);
	Fan->SetupAttachment(RootComponent);
	CoverTop->SetupAttachment(RootComponent);
}

void AConnectableFan::BeginPlay()
{
	Super::BeginPlay();

	//Rotating->SetUpdatedComponent(Fan);
	Rotating->RotationRate = FRotator(0.f, 0.f, 0.f);
}

void AConnectableFan::TurnOn()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Fan turned on"));
	Rotating->SetUpdatedComponent(Fan);
	Rotating->RotationRate = FRotator(0.f, Speed, 0.f);
	bIsOn = true;
}

void AConnectableFan::TurnOff()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Fan turned off"));
	Rotating->RotationRate = FRotator(0.f, 0.f, 0.f);
	bIsOn = false;
}

void AConnectableFan::SetSpeedOne()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Fan speed: 1"));
	Speed = 50;
	if(bIsOn)
		Rotating->RotationRate = FRotator(0.f, Speed, 0.f);
}

void AConnectableFan::SetSpeedTwo()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Fan speed: 2"));
	Speed = 180;
	if (bIsOn)
		Rotating->RotationRate = FRotator(0.f, Speed, 0.f);
}

bool AConnectableFan::CanBePlaced(FHitResult TraceHit, FVector& Location)
{
	if (TraceHit.Normal.Z != -1.f)
		return false;

	Location = TraceHit.Location;

	FVector Min, Max;

	Body->GetLocalBounds(Min, Max);

	Location.Z -= (Max - Min).Z;
	return true;
}

FString AConnectableFan::GetDocInfo()
{
	FString info = Super::GetDocInfo();

	info.Append(FString::SanitizeFloat(Diametr));
	info.Append(",");
	info.Append(Color);
	info.Append(",");
	info.Append(FString::SanitizeFloat(Power));
	info.Append(",");
	info.Append(FString::SanitizeFloat(Mass));
	info.Append(",");
	info.Append(FString::SanitizeFloat(Price));

	return info;
}
