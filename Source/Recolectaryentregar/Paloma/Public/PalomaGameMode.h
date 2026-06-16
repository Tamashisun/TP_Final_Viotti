#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PalomaGameMode.generated.h"

/**
 * Gestiona el timer y el estado de la partida. 
 */
UCLASS()
class RECOLECTARYENTREGAR_API APalomaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;
	
	UFUNCTION(BlueprintCallable)
	void RefreshPlayers();

private:
	void TickCountdown();
	void TickMatchTimer();
	void EndMatch();

protected:
	UPROPERTY(EditAnywhere)
	int CurrentCountdown = 3;

private:
	FTimerHandle CountdownTimerHandle;
	FTimerHandle MatchTimerHandle;
};
