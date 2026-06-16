#include "Paloma/Public/PalomaFruitSpawner.h"

#include "EngineUtils.h"
#include "Paloma/Public/PalomaCollectable.h"

APalomaFruitSpawner::APalomaFruitSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
}

void APalomaFruitSpawner::BeginPlay()
{
    Super::BeginPlay();

    if (!HasAuthority()) return;

    ScheduleNextSpawn(EFruitType::Banana);
    ScheduleNextSpawn(EFruitType::Apple);
    ScheduleNextSpawn(EFruitType::Strawberry);
}

void APalomaFruitSpawner::ScheduleNextSpawn(EFruitType Type)
{
    float MinTime = 1.f;
    float MaxTime = 5.f;
    FTimerHandle* Handle = &BananaTimer;

    switch (Type)
    {
        case EFruitType::Banana:
            MinTime = 1.f; MaxTime = 5.f;
            Handle = &BananaTimer;
            break;
        case EFruitType::Apple:
            MinTime = 5.f; MaxTime = 20.f;
            Handle = &AppleTimer;
            break;
        case EFruitType::Strawberry:
            MinTime = 10.f; MaxTime = 60.f;
            Handle = &StrawberryTimer;
            break;
    }

    float Delay = FMath::RandRange(MinTime, MaxTime);

    GetWorldTimerManager().SetTimer(*Handle, [this, Type]()
    {
        SpawnFruit(Type);
        ScheduleNextSpawn(Type);
    }, Delay, false);
}

void APalomaFruitSpawner::SpawnFruit(EFruitType Type)
{
    if (CountFruitsInWorld() >= MaxFruits) return;

    TSubclassOf<APalomaCollectable> ClassToSpawn = nullptr;
    switch (Type)
    {
        case EFruitType::Banana:     ClassToSpawn = BananaClass;     break;
        case EFruitType::Apple:      ClassToSpawn = AppleClass;      break;
        case EFruitType::Strawberry: ClassToSpawn = StrawberryClass; break;
    }

    if (!ClassToSpawn) return;

    // Posición aleatoria dentro del radio
    FVector Origin = GetActorLocation();
    float RandAngle = FMath::RandRange(0.f, 360.f);
    float RandDist  = FMath::RandRange(0.f, SpawnRadius);
    FVector Offset  = FVector(
        FMath::Cos(FMath::DegreesToRadians(RandAngle)) * RandDist,
        FMath::Sin(FMath::DegreesToRadians(RandAngle)) * RandDist,
        0.f
    );

    FVector SpawnLocation = Origin + Offset;
    FRotator SpawnRotation = FRotator::ZeroRotator;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    APalomaCollectable* Fruit = GetWorld()->SpawnActor<APalomaCollectable>(
        ClassToSpawn, SpawnLocation, SpawnRotation, Params
    );

    if (Fruit)
    {
        Fruit->FruitType = Type;
    }
}

int32 APalomaFruitSpawner::CountFruitsInWorld() const
{
    int32 Count = 0;
    for (TActorIterator<APalomaCollectable> It(GetWorld()); It; ++It)
    {
        Count++;
    }
    return Count;
}