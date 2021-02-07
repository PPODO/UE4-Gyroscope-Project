#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GyroPlayerController.generated.h"

UCLASS()
class GYROTEST_API AGyroPlayerController : public APlayerController {
	GENERATED_BODY()
public:
	AGyroPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float fDeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USocketComponent* m_pSocketComponent;

	TSharedPtr<FInternetAddr> m_pSendAddr;

};