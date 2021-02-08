#include "Actors/GyroActor.h"
#include <GyroTest/Public/PlayerController/GyroPlayerController.h>
#include <Components/StaticMeshComponent.h>
#include <UObject/ConstructorHelpers.h>

#include <GyroTest/Public/Components/SocketComponent.h>

AGyroActor::AGyroActor() {
	m_pStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = m_pStaticMeshComponent;
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshObject(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (staticMeshObject.Succeeded())
		m_pStaticMeshComponent->SetStaticMesh(staticMeshObject.Object);

	
	m_pSocketComponent = CreateDefaultSubobject<USocketComponent>(TEXT("Socket Component"));
	m_pSocketComponent->m_onReceivedDelegate.BindUObject(this, &AGyroActor::OnDataReceived);

	PrimaryActorTick.bCanEverTick = true;
}

void AGyroActor::BeginPlay() {
	Super::BeginPlay();

}

void AGyroActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);


}

void AGyroActor::OnDataReceived(uint8* sMessageBuffer) {
	auto inputMotionData = reinterpret_cast<FInputMotionData*>(sMessageBuffer);
	
	if (inputMotionData) {
		FString sMessageLog;
		switch (inputMotionData->m_MotionType) {
		case EInputMotion::EInput_Tilt:
			sMessageLog.Append(TEXT("Tilt"));
			break;
		case EInputMotion::EInput_RotationRate:
			sMessageLog.Append(TEXT("Rotation Rate"));
			break;
		case EInputMotion::EInput_Gravity:
			sMessageLog.Append(TEXT("Gravity"));
			break;
		case EInputMotion::EInput_Acceleration:
			sMessageLog.Append(TEXT("Acceleration"));
			break;
		}

		sMessageLog.Append(TEXT(" : "));
		sMessageLog.Append(inputMotionData->m_vData.ToString());
		GEngine->AddOnScreenDebugMessage(9, 1.f, FColor::Green, sMessageLog);
	}
}