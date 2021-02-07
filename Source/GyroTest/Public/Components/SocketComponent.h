#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Sockets.h>
#include "SocketComponent.generated.h"

DECLARE_DELEGATE_OneParam(FOnReceivedPacket, uint8*);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GYROTEST_API USocketComponent : public UActorComponent {
	GENERATED_BODY()
public:
	USocketComponent();

	ESocketErrors GetLastErrorCode();
	bool SendTo(uint8* sMessageBuffer, int32 iBytes, FInternetAddr& destination);

	static TSharedPtr<FInternetAddr> CreateInternetAddr(const FString& ipAddress, uint16 wPort);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginDestroy() override;

public:
	FOnReceivedPacket m_onReceivedDelegate;

private:
	FSocket* m_pSocket;
	TSharedPtr<FInternetAddr> m_pRecvedAddr;

	uint8 m_sMessageBuffer[1024];

};