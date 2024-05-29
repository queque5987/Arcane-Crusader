// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"
#include "CMonsterSpawner_Manual.generated.h"

UCLASS()
class MMB_API ACMonsterSpawner_Manual : public AActor
{
	GENERATED_BODY()


protected:
	ACMonsterSpawner_Manual();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SpawnPoint;

	UPROPERTY(EditAnywhere)
	float Radius;

	UPROPERTY(EditAnywhere)
	int MaxMonster;

	UPROPERTY(EditAnywhere)
	float SpawnCounter;

	TArray<class ACEnemyCharacter*> SpawnedMonsters;

	UFUNCTION()
	void OnMonsterDied(AActor* Act);
	void GetCoordinate(FVector& Location);
public:
	class ACEnemyCharacter* SpawnMonster(TSubclassOf<class ACEnemyCharacter> MonsterClass);
};
