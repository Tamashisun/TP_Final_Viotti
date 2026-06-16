#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PalomaCollectable.generated.h"

UENUM(BlueprintType)
enum class EFruitType : uint8
{
	None        UMETA(DisplayName="None"),
	Banana      UMETA(DisplayName = "Banana"),
	Apple       UMETA(DisplayName = "Apple"),
	Strawberry  UMETA(DisplayName = "Strawberry")
};

UCLASS()
class RECOLECTARYENTREGAR_API APalomaCollectable : public AActor
{
	GENERATED_BODY()

public:
	APalomaCollectable();
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated)
	EFruitType FruitType = EFruitType::Banana;

	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 PointValue = 1;

	UPROPERTY(ReplicatedUsing = OnRep_IsPickedUp, BlueprintReadOnly)
	bool bIsPickedUp = false;

	UFUNCTION()
	void OnRep_IsPickedUp();

	UFUNCTION(BlueprintCallable)
	void PickUp();

	virtual void GetLifetimeReplicatedProps(
		TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};