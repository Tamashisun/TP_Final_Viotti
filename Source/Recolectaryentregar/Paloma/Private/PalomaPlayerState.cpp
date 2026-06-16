#include "Paloma/Public/PalomaPlayerState.h"

#include "Paloma/Public/PalomaGameState.h"

void APalomaPlayerState::OnRep_Score()
{
	OnScoreUpdated.Broadcast();
	
	if (UWorld* World = GetWorld())
	{
		if (APalomaGameState* PalomaGS = World->GetGameState<APalomaGameState>())
		{
			PalomaGS->OnRefreshPlayers.Broadcast();
		}
	}
}

int32 APalomaPlayerState::GetSortedPlayerIndex() const
{
	if (const UWorld* World = GetWorld())
	{
		if (const APalomaGameState* PalomaGS = World->GetGameState<APalomaGameState>())
		{
			const TArray<APlayerState*> SortedPlayers = PalomaGS->GetSortedPlayerArray();
			return SortedPlayers.IndexOfByKey(this);
		}
	}

	return INDEX_NONE; // -1 si algo falló
}

void APalomaPlayerState::AddScore(float Value)
{
	const float NewScore = Value + GetScore();
	SetScore(NewScore);
	OnRep_Score();
}

void APalomaPlayerState::ResetScore()
{
	SetScore(0.0f);
	OnRep_Score();
}

