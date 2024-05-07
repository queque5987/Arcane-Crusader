// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWeapon.h"
#include "CWeapon.h"
#include "GameFramework/Actor.h"
#include "CStaff.generated.h"

UCLASS()
class MMB_API ACStaff : public AActor, public IIWeapon
{
	GENERATED_BODY()

public:	
	ACStaff();
	//virtual void LMB_Attack() override;
	//virtual void LMB_Triggered(struct AttackResult& AttackResult) override;
	void LMB_Triggered(struct AttackResult& AttackResult);
	//virtual void LMB_Completed() override;
	//virtual void RMB_Triggered(struct AttackResult& AttackResult) override;
	void RMB_Triggered(struct AttackResult& AttackResult);
	//virtual void RMB_Completed(struct AttackResult& AttackResult) override;
	void RMB_Completed(struct AttackResult& AttackResult);

protected:
	virtual void BeginPlay() override;
	/*UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/
public:	
	virtual void Tick(float DeltaTime) override;
	void Fire(FVector TargetLocation);
	UFUNCTION()
	void OnCastEnd(UAnimMontage* Montage, bool bInterrupted);

	class UStaticMeshComponent* StaticMeshComponent;
	class USphereComponent* Collider;

	TArray<UParticleSystem*> WeaponEffect;
protected:
	float tempDamage0;
	float tempDamage1;
	float tempDamage2;
	float RequiredStamina;

	FName WeaponMesh;

	UPROPERTY(EditAnywhere)
	int32 ItemData_IconTexture;
	UPROPERTY(EditAnywhere)
	int32 ItemData_ItemPrice;
	UPROPERTY(EditAnywhere)
	FString ItemData_AttackType;
	UPROPERTY(EditAnywhere)
	float AttackDamage = 1;
	UPROPERTY(EditAnywhere)
	FName WeaponName;

	bool IsEquiped;
	bool bCasting;
	float CastingClock;
	float DamageScale;
};
