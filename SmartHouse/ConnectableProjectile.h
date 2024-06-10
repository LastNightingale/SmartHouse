// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Connectable.h"
#include "ConnectableProjectile.generated.h"

class UProjectileMovementComponent;

/**
 * 
 */
UCLASS()
class SMARTHOUSE_API AConnectableProjectile : public AConnectable
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;	
public:

	AConnectableProjectile();

	/** Returns CollisionComp subobject **/
	UStaticMeshComponent* GetCollisionComp() const { return Body; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UFUNCTION()
	void SetRed();
	
};
