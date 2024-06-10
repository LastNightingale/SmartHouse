// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Connectable.h"

#include "DeviceDisplayItem.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API UDeviceDisplayItem : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Name;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* IP;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Type;

	Address DeviceIP;

public:

	void SetName(FText name); 

	void SetIP(FText ip); 

	void SetType(FText type); 

	void SetDeviceIP(const Address& deviceIP);

	void SendCommand(const Address& deviceIP, FName CommandName);
};
