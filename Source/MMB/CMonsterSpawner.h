#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "NavigationSystem.h"
#include "CMonsterSpawner.generated.h"

UCLASS()
class MMB_API ACMonsterSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class USphereComponent* SpawnPoint;

	UPROPERTY(EditAnywhere)
	float Radius;

	UPROPERTY(EditAnywhere)
	int MaxMonster;

	UPROPERTY(EditAnywhere)
	float SpawnCounter;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACEnemyCharacter> SpawnMonsterClass;
public:	
	ACMonsterSpawner();

protected:
	virtual void BeginPlay() override;

	TArray<class ACEnemyCharacter*> SpawnedMonsters;
	FTimerHandle SpawnTimerHandler;
public:	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void GetCoordinate(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void GetCoordinate(FVector& Location);
	UFUNCTION()
	void SpawnTick();
};
