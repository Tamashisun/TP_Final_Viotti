#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "PalomaGameState.generated.h"

// Estados de la partida
UENUM(BlueprintType)
enum class EMatchPhase : uint8
{
	WaitingToStart,
	Countdown,
	Playing,
	Finished
};

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerUpdated, float, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged, EMatchPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountdownTick, int32, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRefreshPlayers);

/**
 * Almacena el timer y el estado de la partida. 
 */
UCLASS()
class RECOLECTARYENTREGAR_API APalomaGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Timer
	UPROPERTY(ReplicatedUsing = OnRep_MatchTimer, BlueprintReadOnly, EditDefaultsOnly)
	float MatchTimer = 60.f;
	UFUNCTION()
	void OnRep_MatchTimer();
	UPROPERTY(BlueprintAssignable)
	FOnTimerUpdated OnTimerUpdated;
	void SetMatchTimer(float NewTime);

	// Estado de la partida
	UPROPERTY(ReplicatedUsing = OnRep_MatchPhase, BlueprintReadOnly)
	EMatchPhase MatchPhase = EMatchPhase::WaitingToStart;
	UFUNCTION()
	void OnRep_MatchPhase();
	UPROPERTY(BlueprintAssignable)
	FOnPhaseChanged OnPhaseChanged;
	void SetMatchPhase(EMatchPhase NewPhase);

	// Countdown previo a empezar la partida
	UPROPERTY(ReplicatedUsing = OnRep_CountdownValue, BlueprintReadOnly)
	int32 CountdownValue = 3;
	UFUNCTION()
	void OnRep_CountdownValue();
	UPROPERTY(BlueprintAssignable)
	FOnCountdownTick OnCountdownTick;
	void SetCountdownValue(int32 NewValue);
	
	UPROPERTY(BlueprintAssignable)
	FOnRefreshPlayers OnRefreshPlayers;
	
	UFUNCTION(BlueprintCallable, Category = "Players")
	TArray<APlayerState*> GetSortedPlayerArray() const;
};
