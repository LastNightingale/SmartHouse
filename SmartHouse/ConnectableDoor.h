// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Connectable.h"

#include "Components/TimelineComponent.h"

#include "ConnectableDoor.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API AConnectableDoor : public AConnectable
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Thickness;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	FString Material;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Height;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Width;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Price;

	virtual void BeginPlay() override;

	virtual bool CanBePlaced(FHitResult TraceHit, FVector& Location) override;

	UPROPERTY(EditDefaultsOnly)
	FTimeline DoorTimeLine;

	bool bIsClosed = true;

	bool bIsLocked = false;

	FRotator BasicRotation;

public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* DoorCurve;

	void UpdateDoor();

	UFUNCTION()
	void UpdatePosition(float Alpha);

	UFUNCTION()
	void Lock();

	UFUNCTION()
	void Unlock();

	virtual FString GetDocInfo() override;
};
