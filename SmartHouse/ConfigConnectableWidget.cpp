// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfigConnectableWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void UConfigConnectableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Confirm->OnClicked.AddDynamic(this, &UConfigConnectableWidget::OnConfirmClick);
	Exit->OnClicked.AddDynamic(this, &UConfigConnectableWidget::OnExitClick);
	CheckBoxNone->OnCheckStateChanged.AddDynamic(this, &UConfigConnectableWidget::OnNone);
	CheckBoxDHCP->OnCheckStateChanged.AddDynamic(this, &UConfigConnectableWidget::OnDHCP);
	CheckBoxStatic->OnCheckStateChanged.AddDynamic(this, &UConfigConnectableWidget::OnStatic);

}

void UConfigConnectableWidget::UpdateWidget(AConnectable* Connectable)
{	
	ClearCheck();
	CheckBoxNone->SetIsChecked(true);
	Connected = Connectable;	
	ReloadInfo();
}

void UConfigConnectableWidget::ReloadInfo()
{
	Address IpAddress = Connected->IP;

	FString first, second, third, fourth;

	first.AppendInt(IpAddress.Octets[0]);
	second.AppendInt(IpAddress.Octets[1]);
	third.AppendInt(IpAddress.Octets[2]);
	fourth.AppendInt(IpAddress.Octets[3]);

	FirstOctet->SetText(FText::FromString(first));
	SecondOctet->SetText(FText::FromString(second));
	ThirdOctet->SetText(FText::FromString(third));
	FourthOctet->SetText(FText::FromString(fourth));

	Name->SetText(Connected->GetName());
}

void UConfigConnectableWidget::OnConfirmClick()
{
	if (CheckBoxNone->IsChecked())
	{
		Connected->Disconnect();
		Connected->IP = { 0, 0, 0, 0 };
		Connected->ConnectionType = EConnectionType::NONE;
	}
	if (CheckBoxDHCP->IsChecked())
	{
		Connected->ConnectionType = EConnectionType::DHCP;
	}
	if (CheckBoxStatic->IsChecked())
	{
		Connected->ConnectionType = EConnectionType::STATIC;
		Connected->Disconnect();
		Connected->IP = { (uint8)FCString::Atoi(*FirstOctet->GetText().ToString()), (uint8)FCString::Atoi(*SecondOctet->GetText().ToString()), 
			(uint8)FCString::Atoi(*ThirdOctet->GetText().ToString()), (uint8)FCString::Atoi(*FourthOctet->GetText().ToString()) };
	}

	Connected->SetName(Name->GetText());
	//UpdateWidget(Connected);
	ReloadInfo();
}

void UConfigConnectableWidget::OnExitClick()
{
	this->RemoveFromViewport();
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
	PC->bShowMouseCursor = false;
}

void UConfigConnectableWidget::ClearCheck()
{
	CheckBoxNone->SetIsChecked(false);
	CheckBoxDHCP->SetIsChecked(false);
	CheckBoxStatic->SetIsChecked(false);
}

void UConfigConnectableWidget::OnNone(bool State)
{
	if (!State)
		return;

	ClearCheck();
	CheckBoxNone->SetIsChecked(true);
	FirstOctet->SetIsEnabled(false);
	SecondOctet->SetIsEnabled(false);
	ThirdOctet->SetIsEnabled(false);
	FourthOctet->SetIsEnabled(false);		

	UpdateWidget(Connected);
}

void UConfigConnectableWidget::OnDHCP(bool State)
{
	if (!State)
		return;

	ClearCheck();
	CheckBoxDHCP->SetIsChecked(true);
	FirstOctet->SetIsEnabled(false);
	SecondOctet->SetIsEnabled(false);
	ThirdOctet->SetIsEnabled(false);
	FourthOctet->SetIsEnabled(false);	
}

void UConfigConnectableWidget::OnStatic(bool State)
{
	if (!State)
		return;

	ClearCheck();
	CheckBoxStatic->SetIsChecked(true);
	FirstOctet->SetIsEnabled(true);
	SecondOctet->SetIsEnabled(true);
	ThirdOctet->SetIsEnabled(true);
	FourthOctet->SetIsEnabled(true);
}
