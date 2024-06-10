// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

//#include "Components/EditableText.h"
#include "Connectable.h"

#include "ConfigConnectableWidget.generated.h"

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API UConfigConnectableWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCheckBox* CheckBoxNone;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCheckBox* CheckBoxDHCP;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCheckBox* CheckBoxStatic;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* Name;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* FirstOctet;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* SecondOctet;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* ThirdOctet;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* FourthOctet;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Confirm;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Exit;

	UPROPERTY()
	AConnectable* Connected = nullptr;

public:

	virtual void NativeConstruct() override;

	void UpdateWidget(AConnectable* Connectable);

	void ReloadInfo();

	UFUNCTION()
	void OnConfirmClick();

	UFUNCTION()
	void OnExitClick();

	void ClearCheck();

	UFUNCTION()
	void OnNone(bool State);

	UFUNCTION()
	void OnDHCP(bool State);

	UFUNCTION()
	void OnStatic(bool State);
	
};
