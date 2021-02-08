#include "PlayerController/GyroPlayerController.h"
#include <GyroTest/Public/Components/SocketComponent.h>
#include <Engine/Engine.h>
#include "..\..\Public\PlayerController\GyroPlayerController.h"

AGyroPlayerController::AGyroPlayerController() {
	m_pSocketComponent = CreateDefaultSubobject<USocketComponent>(TEXT("Socket Component"));

	m_currentInputMotionData = EInputMotion::EInput_Tilt;

	PrimaryActorTick.bCanEverTick = true;
}

void AGyroPlayerController::ChangeInputMotionData(EInputMotion inputMotion) {
	m_currentInputMotionData = inputMotion;
}

void AGyroPlayerController::BeginPlay() {
	Super::BeginPlay();

	m_pSendAddr = USocketComponent::CreateInternetAddr(TEXT("172.30.1.10"), 3515);
}

void AGyroPlayerController::Tick(float fDeltaTime) {
	Super::Tick(fDeltaTime);

	if (m_pSocketComponent) {
		FVector vTilt, vRotationRate, vGravity, vAcceleration;
		GetInputMotionState(vTilt,vRotationRate, vGravity, vAcceleration);

		FVector vData;
		switch (m_currentInputMotionData) {
		case EInputMotion::EInput_Tilt:
			vData = FMath::RadiansToDegrees(vTilt);
			break;
		case EInputMotion::EInput_RotationRate:
			vData = FMath::RadiansToDegrees(vRotationRate);
			break;
		case EInputMotion::EInput_Gravity:
			vData = vGravity;
			break;
		case EInputMotion::EInput_Acceleration:
			vData = FMath::RadiansToDegrees(vAcceleration);
			break;
		}

		FInputMotionData motionData(m_currentInputMotionData, vData);
		GEngine->AddOnScreenDebugMessage(8, 1.f, FColor::Yellow, vData.ToString());

		if (!m_pSocketComponent->SendTo(reinterpret_cast<uint8*>(&motionData), sizeof(FInputMotionData), *m_pSendAddr))
			GEngine->AddOnScreenDebugMessage(10, 10.f, FColor::Red, FString::Printf(TEXT("Error! - Send failure, error code is %d"), m_pSocketComponent->GetLastErrorCode()));
	}
}