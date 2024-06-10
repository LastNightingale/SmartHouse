// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectableBall.h"

void AConnectableBall::SetPurple()
{

}

void AConnectableBall::SetRed()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Lamp set red"));
}
