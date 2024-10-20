#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CDestructibleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMB_API UCDestructibleComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UCDestructibleComponent();

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CollisionBody;
protected:
	virtual void BeginPlay() override;
	struct FTimerHandle LifetimeHandle;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
