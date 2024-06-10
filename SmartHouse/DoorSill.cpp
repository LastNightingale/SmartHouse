// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorSill.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoorSill::ADoorSill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sill = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sill"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	SetRootComponent(Sill);
	Box->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoorSill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorSill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

