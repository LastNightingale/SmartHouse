// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Connectable.h"
#include "ConnectableLamp.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API AConnectableLamp : public AConnectable
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	FString Color;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Power;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	FString Material;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Brightness;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Price;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	class UPointLightComponent* Light;

	UFUNCTION()
	void TurnOn();

	UFUNCTION()
	void TurnOff();

	virtual void BeginPlay() override;

public:

	AConnectableLamp();

	virtual bool CanBePlaced(FHitResult TraceHit, FVector& Location) override;

	virtual FString GetDocInfo() override;
	
};
