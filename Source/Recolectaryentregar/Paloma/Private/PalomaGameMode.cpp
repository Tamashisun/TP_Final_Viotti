#include "Paloma/Public/PalomaGameMode.h"

#include "Paloma/Public/PalomaGameState.h"

void APalomaGameMode::BeginPlay()
{
	Super::BeginPlay();
}

bool APalomaGameMode::RequestStartMatch()
{
	if (bMatchStarted)
	{
		return false;
	}

	APalomaGameState* PalomaGameState = GetGameState<APalomaGameState>();
	if (!PalomaGameState || PalomaGameState->PlayerArray.Num() < MinPlayersToStart)
	{
		return false;
	}

	bMatchStarted = true;
	StartCountdown();
	return true;
}

void APalomaGameMode::StartCountdown()
{
	GetWorldTimerManager().SetTimer(
	   CountdownTimerHandle,
	   this,
	   &APalomaGameMode::TickCountdown,
	   1.f,
	   true,
	   1.f
	);
}

void APalomaGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	RefreshPlayers();
}

void APalomaGameMode::RefreshPlayers()
{
	APalomaGameState* PalomaGameState = GetGameState<APalomaGameState>();
	PalomaGameState->OnRefreshPlayers.Broadcast();
}

void APalomaGameMode::TickCountdown()
{
	APalomaGameState* PalomaGameState = GetGameState<APalomaGameState>();

	PalomaGameState->SetMatchPhase(EMatchPhase::Countdown);
	PalomaGameState->SetCountdownValue(CurrentCountdown);

	CurrentCountdown--;

	if (CurrentCountdown < 0)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		PalomaGameState->SetMatchPhase(EMatchPhase::Playing);

		// Arrancamos el timer de la partida
		GetWorldTimerManager().SetTimer(
			MatchTimerHandle,
			this,
			&APalomaGameMode::TickMatchTimer,
			1.f, // Cada 1 segundo
			true // Loop
		);
	}
}

/**
 * Timer de la partida
 */
void APalomaGameMode::TickMatchTimer()
{
	APalomaGameState* PalomaGameState = GetGameState<APalomaGameState>();

	float MatchTimer = PalomaGameState->MatchTimer - 1;
	PalomaGameState->SetMatchTimer(MatchTimer);

	if (PalomaGameState->MatchTimer <= 0.0f)
	{
		PalomaGameState->SetMatchTimer(0.0f);

		GetWorldTimerManager().ClearTimer(MatchTimerHandle);

		EndMatch();
	}
}

/**
 * Finaliza la partida
 */
void APalomaGameMode::EndMatch()
{
	APalomaGameState* PalomaGameState = GetGameState<APalomaGameState>();
	PalomaGameState->SetMatchPhase(EMatchPhase::Finished);
}

