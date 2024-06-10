// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Connectable.h"
#include "DeviceDisplayItem.h"

#include "DeviceDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API UDeviceDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UScrollBox* DeviceDisplayScrollBox;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* PrintButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDeviceDisplayItem> ItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TMap <EDeviceType, TSubclassOf<class UDeviceDisplayItem>> WidgetTypes;

	UPROPERTY(EditDefaultsOnly, Category = "Names")
	TMap <EDeviceType, FText> TypeNames;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* SubnetIPText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* GatewayIPText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* GatewayMaskText;

public:

	virtual void NativeConstruct() override;

	void UpdateInfo(TArray<DeviceInformation> DeviceInfo);

	void ClearInfo();

	UFUNCTION()
	void Exit();

	UFUNCTION()
	void Print();

	void UpdateGatewayInfo(IPMask ipmask, Address);
	
};
