#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "PalomaPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreUpdated);

UCLASS()
class RECOLECTARYENTREGAR_API APalomaPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void OnRep_Score() override;
	
	UFUNCTION(BlueprintCallable, Category = "Players")
	int32 GetSortedPlayerIndex() const;

	UPROPERTY(BlueprintAssignable)
	FOnScoreUpdated OnScoreUpdated;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(float Value);
	UFUNCTION(BlueprintCallable, Category = "Score")
	void ResetScore();
};
