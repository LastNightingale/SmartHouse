// Fill out your copyright notice in the Description page of Project Settings.


#include "CSVFileManager.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"

// Sets default values
ACSVFileManager::ACSVFileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACSVFileManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACSVFileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACSVFileManager::SaveCSVText(FString SaveDirectory, FString Filename, TArray<FString> TextToSave)
{
	SaveDirectory += "\\";
	SaveDirectory += "Filename";

	FString Filestring = "";

	for (FString& Each : TextToSave)
	{
		Filestring += Each;
		Filestring += LINE_TERMINATOR;
	}

	return FFileHelper::SaveStringToFile(Filestring, *SaveDirectory);
}

