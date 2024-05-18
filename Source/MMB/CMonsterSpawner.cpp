// Fill out your copyright notice in the Description page of Project Settings.


#include "CMonsterSpawner.h"
#include "PCH.h"

// Sets default values
ACMonsterSpawner::ACMonsterSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("Spawner"));
	SpawnPoint->SetSphereRadius(Radius);
	SetRootComponent(SpawnPoint);
	SetActorEnableCollision(true);
	//SpawnPoint->SetCollisionEnabled(ECollisionEnabled::);

	SpawnedMonsters.SetNum(MaxMonster);
}

void ACMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnPoint->OnComponentBeginOverlap.AddDynamic(this, &ACMonsterSpawner::GetCoordinate);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandler, this, &ACMonsterSpawner::SpawnTick, SpawnCounter, true);
}

void ACMonsterSpawner::OnMonsterDied(AActor* Act)
{
	UE_LOG(LogTemp, Log, TEXT("Monster has Died %s"), *Act->GetName());
	ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(Act);
	if (IsValid(EC)) SpawnedMonsters.Remove(EC);
}

void ACMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACMonsterSpawner::GetCoordinate(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UNavigationSystemV1* nav = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nav != nullptr)
	{
		FNavLocation NLocation;
		nav->GetRandomReachablePointInRadius(GetActorLocation(), Radius, NLocation);

		DrawDebugSphere(GetWorld(), NLocation.Location, 30.f, 16, FColor::Blue, false, 10.f);

		//Location = NLocation.Location;
	}
}

void ACMonsterSpawner::GetCoordinate(FVector& Location)
{
	Location = GetActorLocation();
	UNavigationSystemV1* nav = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nav != nullptr)
	{
		FNavLocation NLocation;
		nav->GetRandomReachablePointInRadius(GetActorLocation(), Radius, NLocation);

		Location = NLocation.Location;
		DrawDebugSphere(GetWorld(), NLocation.Location, 300.f, 16, FColor::Blue, false, 10.f);

		UE_LOG(LogTemp, Log, TEXT("Random Vector : %s"), Location);
	}
}

void ACMonsterSpawner::SpawnTick()
{
	int T = MaxMonster - SpawnedMonsters.Num();
	FVector SpawnLocation;
	UE_LOG(LogTemp, Log, TEXT("Spawning %d Monsters"), T);

	ACEnemyCharacter* EC = nullptr;
	if (T > 0)
	{
		for (int i = 0; i < T; i++)
		{
			GetCoordinate(SpawnLocation);
			EC = GetWorld()->SpawnActor<ACEnemyCharacter>(SpawnMonsterClass, SpawnLocation + FVector::UpVector * 100.f, FRotator::ZeroRotator);

			if (EC != nullptr)
			{
				SpawnedMonsters.Add(EC);
				EC->OnDestroyed.AddDynamic(this, &ACMonsterSpawner::OnMonsterDied);
				UE_LOG(LogTemp, Log, TEXT("Spawning %d th Monster"), (i + 1));
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Failed to Spawn %d th Monster"), (i + 1));
			}
		}
	}
}

