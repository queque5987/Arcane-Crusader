// Fill out your copyright notice in the Description page of Project Settings.


#include "CMonsterSpawner_Manual.h"
#include "PCH.h"

ACMonsterSpawner_Manual::ACMonsterSpawner_Manual()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("Spawner"));
	//SpawnPoint->SetSphereRadius(Radius);
	SetRootComponent(SpawnPoint);
	SetActorEnableCollision(true);

	SpawnedMonsters.SetNum(MaxMonster);
}

void ACMonsterSpawner_Manual::BeginPlay()
{
	Super::BeginPlay();

}

void ACMonsterSpawner_Manual::OnMonsterDied(AActor* Act)
{
	ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(Act);
	if (IsValid(EC)) SpawnedMonsters.Remove(EC);
}

void ACMonsterSpawner_Manual::GetCoordinate(FVector& Location)
{
	Location = GetActorLocation();
	UNavigationSystemV1* nav = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nav != nullptr)
	{
		FNavLocation NLocation;
		nav->GetRandomReachablePointInRadius(GetActorLocation(), SpawnPoint->GetScaledSphereRadius(), NLocation);

		Location = NLocation.Location;
	}
}

class ACEnemyCharacter* ACMonsterSpawner_Manual::SpawnMonster(TSubclassOf<class ACEnemyCharacter> MonsterClass)
{
	FVector SpawnLocation;
	GetCoordinate(SpawnLocation);
	ACEnemyCharacter* EC = GetWorld()->SpawnActor<ACEnemyCharacter>(MonsterClass, SpawnLocation + FVector::UpVector * 100.f, FRotator::ZeroRotator);

	if (EC != nullptr)
	{
		SpawnedMonsters.Add(EC);
		EC->OnDestroyed.AddDynamic(this, &ACMonsterSpawner_Manual::OnMonsterDied);
		UE_LOG(LogTemp, Log, TEXT("Spawning Monster"));
		return EC;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to Spawn Monster"));
	}
	return nullptr;
}
