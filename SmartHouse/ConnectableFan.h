// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Connectable.h"
#include "ConnectableFan.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API AConnectableFan : public AConnectable
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Diametr;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	FString Color;	

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Power;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Mass;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Price;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UStaticMeshComponent* Fan;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UStaticMeshComponent* CoverTop;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UStaticMeshComponent* CoverBottom;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	class URotatingMovementComponent* Rotating;

	float Speed = 50.f;

	bool bIsOn = false;

	AConnectableFan();

	virtual void BeginPlay() override;

	UFUNCTION()
	void TurnOn();

	UFUNCTION()
	void TurnOff();

	UFUNCTION()
	void SetSpeedOne();

	UFUNCTION()
	void SetSpeedTwo();

	virtual bool CanBePlaced(FHitResult TraceHit, FVector& Location) override;

public:

	virtual FString GetDocInfo() override;
	
};
