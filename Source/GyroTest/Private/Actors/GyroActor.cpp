#include "Actors/GyroActor.h"
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
	UE_LOG(LogTemp, Error, TEXT("Received!"));
}