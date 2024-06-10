// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Connectable.h"
#include "ConnectableTablet.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API AConnectableTablet : public AConnectable
{
	GENERATED_BODY()

public:

	AConnectableTablet();

	void SendCommand(const Address& deviceIP, FName CommandName);

	void Print();

protected:

	virtual void BeginPlay();

	UFUNCTION()
	void UpdateDevices();

	UFUNCTION()
	void ShowTablet();

	FTimerHandle TabletTimerHandle;	

	

};
