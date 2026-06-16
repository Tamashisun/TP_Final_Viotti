#include "Paloma/Public/PalomaGameState.h"

#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

void APalomaGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APalomaGameState, MatchTimer);
	DOREPLIFETIME(APalomaGameState, MatchPhase);
	DOREPLIFETIME(APalomaGameState, CountdownValue);
}

void APalomaGameState::OnRep_MatchTimer()
{
	OnTimerUpdated.Broadcast(MatchTimer);
}

void APalomaGameState::OnRep_MatchPhase()
{
	OnPhaseChanged.Broadcast(MatchPhase);
}

void APalomaGameState::OnRep_CountdownValue()
{
	OnCountdownTick.Broadcast(CountdownValue);
}

void APalomaGameState::SetMatchPhase(EMatchPhase NewPhase)
{
	MatchPhase = NewPhase;
	OnRep_MatchPhase();
}

void APalomaGameState::SetCountdownValue(int32 NewValue)
{
	CountdownValue = NewValue;
	OnRep_CountdownValue();
}

TArray<APlayerState*> APalomaGameState::GetSortedPlayerArray() const
{
	TArray<APlayerState*> SortedPlayers = PlayerArray;

	SortedPlayers.Sort([](const APlayerState& A, const APlayerState& B)
	{
		return A.GetPlayerId() < B.GetPlayerId();
	});

	return SortedPlayers;
}

void APalomaGameState::SetMatchTimer(float NewTime)
{
	MatchTimer = NewTime;
	OnRep_MatchTimer();
}
