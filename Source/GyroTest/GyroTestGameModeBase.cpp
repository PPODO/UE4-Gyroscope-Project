// Copyright Epic Games, Inc. All Rights Reserved.
#include "GyroTestGameModeBase.h"
#include <GyroTest/Public/Actors/GyroActor.h>
#include <GyroTest/Public/PlayerController/GyroPlayerController.h>
#include <UMG/Public/Blueprint/UserWidget.h>
#include <UObject/ConstructorHelpers.h>
#include <Engine/World.h>

AGyroTestGameModeBase::AGyroTestGameModeBase() {
#if PLATFORM_ANDROID
	ConstructorHelpers::FClassFinder<UUserWidget> androidUMG(TEXT("WidgetBlueprint'/Game/UI/BP_AndroidUI'"));
	if (androidUMG.Succeeded())
		m_androidUMGClass = androidUMG.Class;

	PlayerControllerClass = AGyroPlayerController::StaticClass();
#endif
}

void AGyroTestGameModeBase::BeginPlay() {
	Super::BeginPlay();

#if PLATFORM_WINDOWS
	FActorSpawnParameters spawnParam;
	
	GetWorld()->SpawnActor<AGyroActor>(AGyroActor::StaticClass(), FVector(250.f, 0.f, 100.f), FRotator::ZeroRotator, spawnParam);
#else
	m_pAndroidUMGInstance = CreateWidget<UUserWidget>(GetWorld(), m_androidUMGClass);
	if (m_pAndroidUMGInstance)
		m_pAndroidUMGInstance->AddToViewport();
#endif
}