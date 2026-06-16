#pragma once
#include "CoreMinimal.h"
#include "PalomaCollectable.h"
#include "GameFramework/Actor.h"
#include "PalomaFruitSpawner.generated.h"

UCLASS()
class RECOLECTARYENTREGAR_API APalomaFruitSpawner : public AActor
{
	GENERATED_BODY()

public:
	APalomaFruitSpawner();
	virtual void BeginPlay() override;

	// Clases de frutas a spawnear (asignar en Blueprint)
	UPROPERTY(EditDefaultsOnly, Category = "Fruits")
	TSubclassOf<APalomaCollectable> BananaClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fruits")
	TSubclassOf<APalomaCollectable> AppleClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fruits")
	TSubclassOf<APalomaCollectable> StrawberryClass;

	// Máximo de frutas en el mapa al mismo tiempo
	UPROPERTY(EditAnywhere, Category = "Fruits")
	int32 MaxFruits = 20;

	// Radio del área de spawn alrededor del actor
	UPROPERTY(EditAnywhere, Category = "Fruits", BlueprintReadOnly)
	float SpawnRadius = 300.f;

private:
	void ScheduleNextSpawn(EFruitType Type);
	void SpawnFruit(EFruitType Type);
	int32 CountFruitsInWorld() const;

	FTimerHandle BananaTimer;
	FTimerHandle AppleTimer;
	FTimerHandle StrawberryTimer;
};