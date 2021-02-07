#include "Components/SocketComponent.h"
#include <SocketSubsystem.h>
#include <Sockets/Public/IPAddress.h>
#include <Common/UdpSocketBuilder.h>
#include <Engine/Engine.h>

USocketComponent::USocketComponent() {

	PrimaryComponentTick.bCanEverTick = true;
}

void USocketComponent::BeginPlay() {
	Super::BeginPlay();
	
#if PLATFORM_WINDOWS
	bool bCanBind = true;
	auto hostAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBind);

	if (hostAddr->IsValid()) {
		FIPv4Address address;
		FIPv4Address::Parse(hostAddr->ToString(false), address);
		FIPv4Endpoint endPoint(address, 3515);

		m_pSocket = FUdpSocketBuilder(TEXT("Socket")).AsNonBlocking().AsReusable().BoundToEndpoint(endPoint).WithReceiveBufferSize(1024);
		m_pRecvedAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	}
#else
	m_pSocket = FUdpSocketBuilder(TEXT("Socket")).AsNonBlocking().AsReusable().WithSendBufferSize(1024);
#endif
}

void USocketComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	uint32 iPendingData = 0;
	if (m_pSocket && m_pRecvedAddr && m_pSocket->HasPendingData(iPendingData) && iPendingData > 0) {
		int32 iRecvedBytes = 0;

		if (m_pSocket->RecvFrom(m_sMessageBuffer, 1024, iRecvedBytes, *m_pRecvedAddr)) {
			m_onReceivedDelegate.ExecuteIfBound(m_sMessageBuffer);
		}
	}
}

void USocketComponent::BeginDestroy() {
	Super::BeginDestroy();

	if (m_pSocket) {
		m_pSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(m_pSocket);
	}
}

ESocketErrors USocketComponent::GetLastErrorCode() {
	return ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode();
}

bool USocketComponent::SendTo(uint8* sMessageBuffer, int32 iBytes, FInternetAddr& destination) {
	int32 iSentBytes = 0;
	if (m_pSocket)
		return m_pSocket->SendTo(sMessageBuffer, iBytes, iSentBytes, destination);

	return false;
}

TSharedPtr<FInternetAddr> USocketComponent::CreateInternetAddr(const FString& ipAddress, uint16 wPort) {
	auto pInternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid = true;

	pInternetAddr->SetIp(*ipAddress, bIsValid);
	pInternetAddr->SetPort(wPort);

	return pInternetAddr;
}