#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GyroActor.generated.h"

UCLASS()
class GYROTEST_API AGyroActor : public AActor {
	GENERATED_BODY()

public:
	AGyroActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void OnDataReceived(uint8* sMessageBuffer);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* m_pStaticMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class USocketComponent* m_pSocketComponent;

};