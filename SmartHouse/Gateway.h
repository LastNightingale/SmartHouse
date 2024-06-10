// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Connectable.h"
#include "Gateway.generated.h"

UCLASS()
class SMARTHOUSE_API AGateway : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGateway();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	USphereComponent* Range;

	TArray<AConnectable*> Connectables;

	TMap<Address, AConnectable*> ConnectedItems;

	FTimerHandle ConnectionTimerHandle;

	DHCP DHCPProtocol;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void CheckConnection();

	UPROPERTY(EditAnywhere)
	ACSVFileManager* FileManager;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DoAction(const Address& IP, FName FunctionName);

	TArray<DeviceInformation> GatherDeviceInfo();

	void Disconnect(Address IP);

	void Connect(AConnectable* connectable);

	void WriteData();

	DHCP GetDHCP() { return DHCPProtocol; };

};
