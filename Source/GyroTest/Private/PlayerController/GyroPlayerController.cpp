#include "PlayerController/GyroPlayerController.h"
#include <GyroTest/Public/Components/SocketComponent.h>
#include <Engine/Engine.h>

AGyroPlayerController::AGyroPlayerController() {
	m_pSocketComponent = CreateDefaultSubobject<USocketComponent>(TEXT("Socket Component"));

	PrimaryActorTick.bCanEverTick = true;
}

void AGyroPlayerController::BeginPlay() {
	Super::BeginPlay();

	m_pSendAddr = USocketComponent::CreateInternetAddr(TEXT("172.30.1.10"), 3515);
}

void AGyroPlayerController::Tick(float fDeltaTime) {
	Super::Tick(fDeltaTime);

	if (m_pSocketComponent) {
		m_pSocketComponent->SendTo(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(TEXT("1"))), 2, *m_pSendAddr);
	}
}