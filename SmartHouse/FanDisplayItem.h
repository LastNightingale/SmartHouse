// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeviceDisplayItem.h"
#include "FanDisplayItem.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API UFanDisplayItem : public UDeviceDisplayItem
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* TurnOnButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* TurnOffButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* SetSpeedOneButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* SetSpeedTwoButton;

	UFUNCTION()
	void OnTurnOnClick();

	UFUNCTION()
	void OnTurnOffClick();

	UFUNCTION()
	void OnSetSpeedOneClick();

	UFUNCTION()
	void OnSetSpeedTwoClick();

public:

	virtual void NativeConstruct() override;
	
};
