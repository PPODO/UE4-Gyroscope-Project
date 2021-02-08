#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GyroPlayerController.generated.h"

UENUM(BlueprintType)
enum class EInputMotion : uint8 {
	EInput_Tilt,
	EInput_RotationRate,
	EInput_Gravity,
	EInput_Acceleration
};

struct FInputMotionData {
public:
	EInputMotion m_MotionType;
	FVector m_vData;

public:
	FInputMotionData() : m_MotionType(EInputMotion::EInput_Tilt), m_vData(FVector::ZeroVector) {};
	FInputMotionData(EInputMotion motionType, const FVector& vData) : m_MotionType(motionType), m_vData(vData) {};

};

UCLASS()
class GYROTEST_API AGyroPlayerController : public APlayerController {
	GENERATED_BODY()
public:
	AGyroPlayerController();

	UFUNCTION(BlueprintCallable)
		void ChangeInputMotionData(EInputMotion inputMotion);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float fDeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USocketComponent* m_pSocketComponent;

	TSharedPtr<FInternetAddr> m_pSendAddr;

	EInputMotion m_currentInputMotionData;

};