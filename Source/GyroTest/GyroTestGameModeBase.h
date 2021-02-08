#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GyroTestGameModeBase.generated.h"

UCLASS()
class GYROTEST_API AGyroTestGameModeBase : public AGameModeBase {
	GENERATED_BODY()
public:
	AGyroTestGameModeBase();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UUserWidget> m_androidUMGClass;
	class UUserWidget* m_pAndroidUMGInstance;

};