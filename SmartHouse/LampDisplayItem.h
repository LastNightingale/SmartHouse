// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeviceDisplayItem.h"
#include "LampDisplayItem.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API ULampDisplayItem : public UDeviceDisplayItem
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* TurnOnButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* TurnOffButton;

	UFUNCTION()
	void OnTurnOnClick();

	UFUNCTION()
	void OnTurnOffClick();

public:

	virtual void NativeConstruct() override;
	
};
