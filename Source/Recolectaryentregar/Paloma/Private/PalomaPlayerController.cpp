#include "Paloma/Public/PalomaPlayerController.h"
#include "Paloma/Public/PalomaGameMode.h"
#include "GameFramework/PlayerState.h"

void APalomaPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnFinishPossession();
}

void APalomaPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	OnFinishPossession();
}

void APalomaPlayerController::Server_SetPlayerName_Implementation(const FString& NewName)
{
	if (APlayerState* PS = GetPlayerState<APlayerState>())
	{
		PS->SetPlayerName(NewName);
	}
}
//void APalomaPlayerController::Server_RequestStartMatch_Implementation()
//{
//	if (APalomaGameMode* PalomaGameMode = GetWorld()->GetAuthGameMode<APalomaGameMode>())
//	{
//		PalomaGameMode->RequestStartMatch();
//	}
//}