// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Connectable.generated.h"

DECLARE_DELEGATE(Command)

struct Address
{

	union
	{
		uint8 Octets[4];
		uint32 Full;
	};

	Address() = default;

	Address(uint8 f, uint8 s, uint8 th, uint8 fr)
	{
		Octets[0] = f;
		Octets[1] = s;
		Octets[2] = th;
		Octets[3] = fr;
	}

	void operator = (const Address& address)
	{
		Octets[0] = address.Octets[0];
		Octets[1] = address.Octets[1];
		Octets[2] = address.Octets[2];
		Octets[3] = address.Octets[3];
	}

	Address operator ++()
	{
		if (Octets[3] < 255)
		{
			Octets[3]++;
			return *this;
		}
		else if (Octets[2] < 255)
		{
			Octets[2]++;
			return *this;
		}
		else if (Octets[1] < 255)
		{
			Octets[1]++;
			return *this;
		}
		else if (Octets[0] < 255)
		{
			Octets[0]++;
			return *this;
		}
		return *this;
	}

	Address GetNext()
	{
		Address temp = *this;
		return ++temp;
	}

	bool operator == (const Address& other) const
	{
		return (Octets[0] == other.Octets[0]) && (Octets[1] == other.Octets[1]) && (Octets[2] == other.Octets[2]) && (Octets[3] == other.Octets[3]);
	}

	friend uint32 GetTypeHash(const Address& address)
	{
		return address.Full;
	}

	FString ToString()
	{
		return FString::Printf(TEXT("%d.%d.%d.%d"), Octets[0], Octets[1], Octets[2], Octets[3]);
	}
};

struct IPMask
{
	Address IP;
	Address SubnetMask;

	IPMask() = default;

	IPMask(const Address& ip, const Address& submask) : IP(ip), SubnetMask(submask)
	{}

	void operator = (const IPMask& ipmask)
	{
		IP = ipmask.IP;
		SubnetMask = ipmask.SubnetMask;
	}
};

class DHCP;

class AGateway;

class DHCP
{
public:
	IPMask GatewayIP;
	Address SubnetIP;
	Address first_range;
	Address last_range;
	Address last_given;

public:
	void Init(const IPMask& ipmask)
	{
		GatewayIP = ipmask;
		SubnetIP.Octets[0] = ApplyMask(GatewayIP.IP.Octets[0], GatewayIP.SubnetMask.Octets[0]);
		SubnetIP.Octets[1] = ApplyMask(GatewayIP.IP.Octets[1], GatewayIP.SubnetMask.Octets[1]);
		SubnetIP.Octets[2] = ApplyMask(GatewayIP.IP.Octets[2], GatewayIP.SubnetMask.Octets[2]);
		SubnetIP.Octets[3] = ApplyMask(GatewayIP.IP.Octets[3], GatewayIP.SubnetMask.Octets[3]);

		last_range.Octets[0] = GatewayIP.IP.Octets[0] | ~GatewayIP.SubnetMask.Octets[0];
		last_range.Octets[1] = GatewayIP.IP.Octets[1] | ~GatewayIP.SubnetMask.Octets[1];
		last_range.Octets[2] = GatewayIP.IP.Octets[2] | ~GatewayIP.SubnetMask.Octets[2];
		last_range.Octets[3] = (GatewayIP.IP.Octets[3] | ~GatewayIP.SubnetMask.Octets[3]) - 1;

		first_range = SubnetIP.GetNext();

		last_given = first_range;
		//++SubnetIP;
	}

	uint8 ApplyMask(uint8 IP, uint8 Mask)
	{
		int bitmask = 1;
		uint8 applied = 0;
		uint8 current_power = 1;
		for (int i = 0; i < 8; i++)
		{
			if ((Mask & bitmask) && (IP & bitmask))
				applied += current_power;

			current_power *= 2;
			bitmask <<= 1;
		}
		return applied;
	}
};

UENUM(BlueprintType)
enum class EDeviceType : uint8
{
	TABLET = 0 UMETA(DisplayName = "TABLET"),
	LAMP = 1 UMETA(DisplayName = "LAMP"),
	FAN = 2  UMETA(DisplayName = "FAN"),
	DOOR = 3  UMETA(DisplayName = "DOOR")
};

UENUM(BlueprintType)
enum class EConnectionType : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	DHCP = 1 UMETA(DisplayName = "DHCP"),
	STATIC = 2  UMETA(DisplayName = "STATIC")
};

struct DeviceInformation
{
	FText Name;
	TEnumAsByte<EDeviceType> DeviceType;
	Address IP;
};

struct ConfigDeviceInformation 
{
	TEnumAsByte<EConnectionType> ConnectionType;
	Address IP;
};

UCLASS()
class SMARTHOUSE_API AConnectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConnectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "DeviceInfo")
	FText Name;

	UPROPERTY(EditDefaultsOnly, Category = "DeviceInfo")
	TEnumAsByte<EDeviceType> DeviceType;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UStaticMeshComponent* Body;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	class UBoxComponent* Box;

	UPROPERTY()
	AGateway* ConnectedGateway = nullptr;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	Command LastCommand;

	//DHCP DHCPProtocol;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	inline bool IsConnected() { return ConnectedGateway != nullptr; };

	inline void Connect(AGateway* gateway) { ConnectedGateway = gateway; };

	inline void Disconnect();

	void RecieveCommand(FName CommandName);

	virtual bool CanBePlaced(FHitResult TraceHit, FVector& Location);

	FText GetName() { return Name; };

	void SetName(FText NewName) { Name = NewName; };

	TEnumAsByte<EDeviceType> GetDeviceType() { return DeviceType; };

	UStaticMeshComponent* GetBody() { return Body; };

	Address IP;

	TEnumAsByte<EConnectionType> ConnectionType = EConnectionType::NONE;

	class UBoxComponent* GetBox() { return Box; };

	virtual FString GetDocInfo();


};


