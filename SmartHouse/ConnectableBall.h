// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Connectable.h"
#include "ConnectableBall.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API AConnectableBall : public AConnectable
{
	GENERATED_BODY()

public:

	void SetPurple();

	UFUNCTION()
	void SetRed();
	
};
