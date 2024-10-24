#pragma once

#include "CoreMinimal.h"
#include "CMonsterSpawner_Manual.h"
#include "Components/SphereComponent.h"
#include "NavigationSystem.h"
#include "CMonsterSpawner.generated.h"

UCLASS()
class MMB_API ACMonsterSpawner : public ACMonsterSpawner_Manual
{
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere)
	//class USphereComponent* SpawnPoint;

	//UPROPERTY(EditAnywhere)
	//float Radius;

	//UPROPERTY(EditAnywhere)
	//int MaxMonster;

	//UPROPERTY(EditAnywhere)
	//float SpawnCounter;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACEnemyCharacter> SpawnMonsterClass;
public:	
	ACMonsterSpawner();

	//UFUNCTION()
	//void OnMonsterDied(AActor* Act);
protected:
	virtual void BeginPlay() override;

	//TArray<class ACEnemyCharacter*> SpawnedMonsters;
	FTimerHandle SpawnTimerHandler;
public:	
	virtual void Tick(float DeltaTime) override;
	//UFUNCTION()
	//void GetCoordinate(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//void GetCoordinate(FVector& Location);
	UFUNCTION()
	void SpawnTick();
};
