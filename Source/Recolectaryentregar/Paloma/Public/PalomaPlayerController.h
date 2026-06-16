#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PalomaPlayerController.generated.h"

UCLASS()
class RECOLECTARYENTREGAR_API APalomaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Player")
	void Server_SetPlayerName(const FString& NewName);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnFinishPossession();

protected:
	// Server: se llama al poseer un pawn
	virtual void OnPossess(APawn* InPawn) override;
	// Client: se llama cuando el cliente reconoce la posesion
	virtual void AcknowledgePossession(APawn* P) override;
};

