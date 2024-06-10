// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectableProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AConnectableProjectile::AConnectableProjectile()
{
	RootComponent = Body;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = Body;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	//ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = 3.0f;
}

void AConnectableProjectile::SetRed()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SET RED"));
}
