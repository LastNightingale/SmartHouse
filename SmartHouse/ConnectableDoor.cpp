// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectableDoor.h"
#include "DoorSill.h"
#include "Components/BoxComponent.h"

void AConnectableDoor::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat Progress;
	Progress.BindUFunction(this, FName("UpdatePosition"));

	FOnTimelineEvent Finished;


	DoorTimeLine.AddInterpFloat(DoorCurve, Progress);

	//UpdateDoor();
}

bool AConnectableDoor::CanBePlaced(FHitResult TraceHit, FVector& Location)
{

	if (ADoorSill* Sill = Cast<ADoorSill>(TraceHit.GetActor()))
	{
		//Location = TraceHit.Location;
		//Location = GetActorLocation();
		Location = Sill->Box->GetComponentLocation();

		FBoxSphereBounds Bounds = Sill->Sill->GetStaticMesh()->GetBounds();

		//Location.X -= (Bounds.GetBox().Max.X - Bounds.GetBox().Min.X) / 4.f;		
		BasicRotation = Sill->GetActorRotation();

		SetActorRotation(BasicRotation);
		return true;
	}

	return false;	
}

void AConnectableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorTimeLine.TickTimeline(DeltaTime);
}

void AConnectableDoor::UpdateDoor()
{
	if (bIsLocked)
		return;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("UpdateDoor"));
	if (bIsClosed)
	{
		bIsClosed = false;
		DoorTimeLine.Play();
	}		
	else
	{
		bIsClosed = true;
		DoorTimeLine.Reverse();
	}		
}

void AConnectableDoor::UpdatePosition(float Alpha)
{
	float DoorRotation = FMath::Lerp(BasicRotation.Yaw, BasicRotation.Yaw - 90.f, Alpha);
	Body->SetRelativeRotation(FRotator(0.f, DoorRotation, 0.f));
}

void AConnectableDoor::Lock()
{
	if (bIsClosed)
		bIsLocked = true;
}

void AConnectableDoor::Unlock()
{
	bIsLocked = false;
}

FString AConnectableDoor::GetDocInfo()
{
	FString info = Super::GetDocInfo();

	info.Append(FString::SanitizeFloat(Thickness));
	info.Append(",");
	info.Append(Material);
	info.Append(",");
	info.Append(FString::SanitizeFloat(Height));
	info.Append(",");
	info.Append(FString::SanitizeFloat(Width));
	info.Append(",");
	info.Append(FString::SanitizeFloat(Price));

	return info;
}
