// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeviceDisplayItem.h"
#include "DoorDisplayItem.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API UDoorDisplayItem : public UDeviceDisplayItem
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* LockButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* UnlockButton;

	UFUNCTION()
	void OnLockClick();

	UFUNCTION()
	void OnUnlockClick();

public:

	virtual void NativeConstruct() override;
	
};
