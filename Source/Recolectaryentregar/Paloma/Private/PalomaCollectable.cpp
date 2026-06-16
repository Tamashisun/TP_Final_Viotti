#include "Paloma/Public/PalomaCollectable.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

APalomaCollectable::APalomaCollectable()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(50.f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void APalomaCollectable::BeginPlay()
{
	Super::BeginPlay();
	switch (FruitType)
	{
	case EFruitType::Banana:     PointValue = 1; break;
	case EFruitType::Apple:      PointValue = 2; break;
	case EFruitType::Strawberry: PointValue = 3; break;
	}
}

void APalomaCollectable::GetLifetimeReplicatedProps(
	TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APalomaCollectable, FruitType);
	DOREPLIFETIME(APalomaCollectable, PointValue);
	DOREPLIFETIME(APalomaCollectable, bIsPickedUp);
}

void APalomaCollectable::OnRep_IsPickedUp()
{
	Mesh->SetVisibility(!bIsPickedUp);
	CollisionSphere->SetCollisionEnabled(
		bIsPickedUp ? ECollisionEnabled::NoCollision
					: ECollisionEnabled::QueryOnly
	);
}

void APalomaCollectable::PickUp()
{
	if (HasAuthority() && !bIsPickedUp)
	{
		bIsPickedUp = true;
		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		OnRep_IsPickedUp();
		Destroy();
	}
}