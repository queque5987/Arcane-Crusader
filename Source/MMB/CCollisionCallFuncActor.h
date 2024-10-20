#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "CCollisionCallFuncActor.generated.h"

UCLASS()
class MMB_API ACCollisionCallFuncActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCollisionCallFuncActor();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collider;
	UPROPERTY(EditAnywhere)
	int32 CallFuncIndex;
	UPROPERTY(EditAnywhere)
	bool bReusable;
protected:
	bool Called;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void CallFunc0();
	void CallFunc1(class ACPlayerCharacter* Player);
	void CallFunc2(class ACPlayerCharacter* Player);
	void CallFunc3(class ACPlayerCharacter* Player);
	void CallFunc4(class ACPlayerCharacter* Player);
public:
	virtual void Tick(float DeltaTime) override;
private:
	AActor* FindActorByTag(TSubclassOf<AActor> FindClass, FName Tag);
};
