// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TabletWidgetItem.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API UTabletWidgetItem : public UUserWidget
{
	GENERATED_BODY()

protected:	

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* SwitchButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* DeviceName;

public:

	virtual void NativeConstruct() override;
	
};
