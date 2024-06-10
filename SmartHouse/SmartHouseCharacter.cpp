// Copyright Epic Games, Inc. All Rights Reserved.

#include "SmartHouseCharacter.h"
#include "SmartHouseProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Gateway.h"
#include "ConnectableTablet.h"
#include "ConnectableDoor.h"
#include "SmartHousePlayerController.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASmartHouseCharacter

ASmartHouseCharacter::ASmartHouseCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ASmartHouseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASmartHouseCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ASmartHouseCharacter::OnOverlapEnd);	

	//GetWorld()->GetTimerManager().SetTimer(TabletTimerHandle, this, &ASmartHouseCharacter::UpdateDevices, 3.f, true);

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.Owner = this;

	ConnectedTablet = GetWorld()->SpawnActor<AConnectableTablet>(TabletClass, Mesh1P->GetSocketLocation(TEXT("TabletSocket")), 
		Mesh1P->GetSocketRotation(TEXT("TabletSocket")), ActorSpawnParams);

	FAttachmentTransformRules Rules{ EAttachmentRule::KeepWorld, false };

	ConnectedTablet->AttachToActor(this, Rules, TEXT("TabletSocket"));
	
	MoveIgnoreActorAdd(ConnectedTablet);
}

//////////////////////////////////////////////////////////////////////////// Input

void ASmartHouseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASmartHouseCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASmartHouseCharacter::Look);

		EnhancedInputComponent->BindAction(RedAction, ETriggerEvent::Started, this, &ASmartHouseCharacter::Interact);

		EnhancedInputComponent->BindAction(PlaceAction, ETriggerEvent::Started, this, &ASmartHouseCharacter::PlaceItem);

		EnhancedInputComponent->BindAction(OpenTabletAction, ETriggerEvent::Started, this, &ASmartHouseCharacter::ShowTablet);

		EnhancedInputComponent->BindAction(OpenDoorAction, ETriggerEvent::Started, this, &ASmartHouseCharacter::OpenDoor);

		EnhancedInputComponent->BindAction(PushAction, ETriggerEvent::Started, this, &ASmartHouseCharacter::PushCurrent);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ASmartHouseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ASmartHouseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASmartHouseCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AGateway* gateway = Cast<AGateway>(OtherActor))
	{
		ConnectedGateway = gateway;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ConnectedPlayer"));
		GetController<ASmartHousePlayerController>()->TabletUI->SetText(FText::FromString("Connected!"));
	}
		
}

void ASmartHouseCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AGateway* gateway = Cast<AGateway>(OtherActor))
	{
		ConnectedGateway = nullptr;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DisconnectedPlayer"));
		GetController<ASmartHousePlayerController>()->TabletUI->SetText(FText::FromString("Disconnected!"));
	}
		
}

void ASmartHouseCharacter::SetRed()
{
	if (ConnectedGateway)
		ConnectedGateway->DoAction({ 10, 192, 0, 2 }, FName(TEXT("SetRed")));
}

void ASmartHouseCharacter::Interact()
{
	FVector TraceStart{ GetPawnViewLocation() };
	FVector TraceEnd{ GetPawnViewLocation() + GetViewRotation().Vector() * 500.f };

	FHitResult TraceHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("PlaceItem"));

	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Emerald, false, 1.f, 0, 2.0f);

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if (AConnectable* connectable = Cast<AConnectable>(TraceHit.GetActor()))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("TracedConnectable"));
			ASmartHousePlayerController* PC = GetController<ASmartHousePlayerController>();
			PC->UpdateConfig(connectable);
			PC->ShowConfig();
		}
	}
}

void ASmartHouseCharacter::PlaceItem()
{
	if (Items.IsEmpty())
		return;

	FVector TraceStart{ GetPawnViewLocation() };
	FVector TraceEnd{ GetPawnViewLocation() + GetViewRotation().Vector() * 1500.f};

	FHitResult TraceHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("PlaceItem"));

	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.f, 0, 2.0f);

	FActorSpawnParameters ActorSpawnParams;

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{

		if (AConnectable* Existed = Cast<AConnectable>(TraceHit.GetActor()))
		{
			Existed->Disconnect();
			Existed->Destroy();
			return;
		}


		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OutActors : %s"), *TraceHit.Normal.ToString()));

		AConnectable* Item = GetWorld()->SpawnActor<AConnectable>(Items[Current], TraceHit.Location, /*GetActorRotation()*/
			FRotator(0.f), ActorSpawnParams);

		FVector Min, Max, NewLocation;

		//Item->GetBody()->GetLocalBounds(Min, Max);
		//FBoxSphereBounds Bounds = Item->GetBox()->GetLocalBounds();

		//Bounds.GetBox().GetSize().Z;

		//NewLocation.Z += (Max.Z - Min.Z) / 2.f;
		//NewLocation.Z += Bounds.GetBox().GetSize().Z / 2.f;

		//auto info = Item->GetDocInfo();

		if (Item->CanBePlaced(TraceHit, NewLocation))
		{
			Item->SetActorLocation(NewLocation);

			/*FRotator Rotation = GetActorRotation();
			Rotation.Yaw += 90.f;
			Item->SetActorRotation(Rotation);*/
			//Item->AddActorWorldRotation(GetActorRotation());
		}
		else
		{
			Item->Destroy();
		}
		
	}
}

void ASmartHouseCharacter::OpenDoor()
{
	FVector TraceStart{ GetPawnViewLocation() };
	FVector TraceEnd{ GetPawnViewLocation() + GetViewRotation().Vector() * 1500.f };

	FHitResult TraceHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("PlaceItem"));

	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.f, 0, 2.0f);

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{

		if (AConnectableDoor* Existed = Cast<AConnectableDoor>(TraceHit.GetActor()))
		{
			Existed->UpdateDoor();
		}

	}
}

void ASmartHouseCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ASmartHouseCharacter::GetHasRifle()
{
	return bHasRifle;
}

void ASmartHouseCharacter::UpdateDevices()
{
	/*if (!ConnectedGateway)
		return;

	ASmartHousePlayerController* PC = GetController<ASmartHousePlayerController>();
	PC->UpdateDevices(ConnectedGateway);*/
}

void ASmartHouseCharacter::ShowTablet()
{
	ASmartHousePlayerController* PC = GetController<ASmartHousePlayerController>();
	PC->ConnectedTablet = this->ConnectedTablet;
	PC->ShowTablet();
}

void ASmartHouseCharacter::PushCurrent()
{
	if (Items.Num() - Current == 1)
		Current = 0;
	else
		Current++;
}
