// Fill out your copyright notice in the Description page of Project Settings.


#include "Gateway.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "CSVFileManager.h"

// Sets default values
AGateway::AGateway()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Range = CreateDefaultSubobject<USphereComponent>("Range");
	SetRootComponent(Range);
}

// Called when the game starts or when spawned
void AGateway::BeginPlay()
{
	Super::BeginPlay();

	Range->OnComponentBeginOverlap.AddDynamic(this, &AGateway::OnOverlapBegin);

	GetWorld()->GetTimerManager().SetTimer(ConnectionTimerHandle, this, &AGateway::CheckConnection, 1.f, true);

	DHCPProtocol.Init({ { 10, 192, 0, 1 }, {255, 240, 0, 0} });

	Range->SetSphereRadius(50.f);
	
}

void AGateway::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlapped"));
	if (AConnectable* connectable = Cast<AConnectable>(OtherActor))
	{
		if (connectable->IsConnected())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Added Collectable : %d"), Connectables.Num()));
			Connectables.Add(connectable);
		}		
	}*/
}

void AGateway::CheckConnection()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Connection check"));

	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));	

	TArray<AActor*> ignoreActors;
	ignoreActors.Init(this, 1);

	TArray<AActor*> outActors;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Range->GetComponentLocation(), 1000.f, 
		traceObjectTypes, AConnectable::StaticClass(), ignoreActors, outActors);

	//DrawDebugSphere(GetWorld(), Range->GetComponentLocation(), 1000.f, 2, FColor::Blue, false, 1.f, 0, 2.f);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OutActors : %d"), outActors.Num()));

	for (AActor* connectable : outActors)
	{
		AConnectable* connect = Cast<AConnectable>(connectable);
		if (!connect->IsConnected())
		{
			Connect(connect);
		}
	}

	/*if (AConnectable* connectable = Cast<AConnectable>(OtherActor))
	{
		if (connectable->IsConnected())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Added Collectable : %d"), Connectables.Num()));
			Connectables.Add(connectable);
		}
	}*/
}

// Called every frame
void AGateway::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGateway::DoAction(const Address& IP, FName FunctionName)
{
	//const auto& test = GatherDeviceInfo();
	auto Num = ConnectedItems.Num();
	if (ConnectedItems.Contains(IP))
		ConnectedItems[IP]->RecieveCommand(FunctionName);
}

TArray<DeviceInformation> AGateway::GatherDeviceInfo()
{
	TArray<DeviceInformation> GatheredInfo;
	for (const TPair<Address, AConnectable*>& connection : ConnectedItems)
	{
		GatheredInfo.Add({connection.Value->GetName(), connection.Value->GetDeviceType(), connection.Key});
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Info : %d"), ConnectedItems.Num()));

	return GatheredInfo;
}

void AGateway::Disconnect(Address IP)
{
	ConnectedItems.Remove(IP);
}

void AGateway::Connect(AConnectable* connectable)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Added Collectable : %d"), Connectables.Num()));
	if (connectable->ConnectionType == EConnectionType::NONE)
		return;

	if (connectable->ConnectionType == EConnectionType::DHCP)
	{
		ConnectedItems.Add(DHCPProtocol.last_given, connectable);
		connectable->IP = DHCPProtocol.last_given;
		++DHCPProtocol.last_given;
		//Connectables.Add(connect);
		connectable->Connect(this);
		//WriteData(); ///////////////////////////////////////
		return;
	}
	else
	{
		if (!ConnectedItems.Contains(connectable->IP))
		{
			connectable->Connect(this);
			ConnectedItems.Add(connectable->IP, connectable);
		}
			
	}
	
}

void AGateway::WriteData()
{
	if (!FileManager)
		return;


	TArray<FString> data;
	FString info;
	//FString temp = "";

	for (const TPair<Address, AConnectable*>& connection : ConnectedItems)
	{
		if (connection.Value->GetDeviceType() == EDeviceType::TABLET)
			continue;

		info = connection.Value->GetDocInfo();		
		data.Add(info);
	}

	auto path = FPaths::GameSourceDir();

	FileManager->SaveCSVText(FPaths::GameSourceDir(), "Doc.csv", data);
}

