// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Connectable.h"

#include "TabletWidget.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API UTabletWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextConnected;

public:

	virtual void NativeConstruct() override;

	void SetText(FText text);
	
};
