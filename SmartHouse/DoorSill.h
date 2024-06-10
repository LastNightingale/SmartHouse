// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorSill.generated.h"

UCLASS()
class SMARTHOUSE_API ADoorSill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorSill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UStaticMeshComponent* Sill;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	class UBoxComponent* Box;

};
