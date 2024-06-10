// Fill out your copyright notice in the Description page of Project Settings.


#include "Connectable.h"
#include "Gateway.h"
#include "Components/BoxComponent.h"

// Sets default values
AConnectable::AConnectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	SetRootComponent(Body);
	Box->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AConnectable::BeginPlay()
{
	Super::BeginPlay();

	Body->OnComponentBeginOverlap.AddDynamic(this, &AConnectable::OnOverlapBegin);
	Body->OnComponentEndOverlap.AddDynamic(this, &AConnectable::OnComponentEndOverlap);

	//DHCPProtocol.Init({ { 10, 192, 0, 1 }, {255, 240, 0, 0} }); 
	
}

void AConnectable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (AGateway* gateway = Cast<AGateway>(OtherActor))
	{
		if (!ConnectedGateway)
			ConnectedGateway = gateway;
	}*/
}

void AConnectable::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AGateway* gateway = Cast<AGateway>(OtherActor))
	{
		Disconnect();
	}
}

void AConnectable::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AGateway* gateway = Cast<AGateway>(OtherActor))
	{
		Disconnect();
	}
}

// Called every frame
void AConnectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

inline void AConnectable::Disconnect()
{
	if (!ConnectedGateway)
		return;

	ConnectedGateway->Disconnect(IP);
	ConnectedGateway = nullptr;
	
}

void AConnectable::RecieveCommand(FName CommandName)
{
	LastCommand.BindUFunction(this, CommandName);
	LastCommand.ExecuteIfBound();
}

bool AConnectable::CanBePlaced(FHitResult TraceHit, FVector& Location)
{
	return false;
}

FString AConnectable::GetDocInfo()
{
	FString info = "";
	info.Append(FindObject<UEnum>(ANY_PACKAGE, TEXT("EDeviceType"))->GetNameStringByValue(static_cast<uint32>(DeviceType.GetIntValue())));
	info.Append(",");
	info.Append(Name.ToString());	
	info.Append(",");
	//info.Append(Name.ToString());	
	
	return info;
}

