// Copyright Epic Games, Inc. All Rights Reserved.
#include "GyroTestGameModeBase.h"
#include <GyroTest/Public/Actors/GyroActor.h>
#include <GyroTest/Public/PlayerController/GyroPlayerController.h>
#include <Engine/World.h>

AGyroTestGameModeBase::AGyroTestGameModeBase() {
#if PLATFORM_ANDROID
	PlayerControllerClass = AGyroPlayerController::StaticClass();
#endif
}

void AGyroTestGameModeBase::BeginPlay() {
	Super::BeginPlay();
	
#if PLATFORM_WINDOWS
	FActorSpawnParameters spawnParam;

	GetWorld()->SpawnActor<AGyroActor>(AGyroActor::StaticClass(), FVector(250.f, 0.f, 100.f), FRotator::ZeroRotator, spawnParam);
#endif
}