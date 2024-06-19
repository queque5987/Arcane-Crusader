// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWeapon.h"
#include "GameFramework/Actor.h"
#include "CRifleStaff.generated.h"

UCLASS()
class MMB_API ACRifleStaff : public AActor, public IIWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACRifleStaff();

	class UStaticMeshComponent* StaticMeshComponent;
	class USphereComponent* Collider;

	TArray<UParticleSystem*> WeaponEffect;
	TArray<USoundBase*> WeaponSoundEffect;
	class USoundCue* StaffMeleeHitSoundCue;

	class UParticleSystemComponent* FireSocketEffectComponent;
	virtual void LMB_Triggered(struct AttackResult& AttackResult) override;
	virtual void LMB_Completed(struct AttackResult& AttackResult) override;
	virtual void RMB_Triggered(struct AttackResult& AttackResult) override;
	virtual void RMB_Completed(struct AttackResult& AttackResult) override;
	virtual void SetIsEquiped(bool e) override;
	virtual void SetAttackDamage(float e) override { AttackDamage = e; }
	virtual void SetBulletType(int32 e) override;
	virtual void SetItemStat(struct ItemStat* ItemStats) override;
	virtual void SetWeaponName(FName e) override { WeaponName = e; }
	//UFUNCTION()
	//void OnPickUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//Bullet Stat
	struct ItemStat* ItemStatus;

	int32 BulletType;
	float AttackRange = 2500.f;
	float BulletSpeed = 100.f;
	float ConstAttackCoolDown = 0.8f;
	//
	float tempDamage0;
	float tempDamage1;
	float tempDamage2;
	float RequiredStamina;

	float AttackCoolDown = 0.f;

	FName WeaponMesh;
	UStaticMeshSocket* FireSocket;

	UPROPERTY(EditAnywhere)
	FName ItemDTRowName;
	UPROPERTY(EditAnywhere)
	FString ItemDTDetail;
	UPROPERTY(EditAnywhere)
	FString ItemData_IconTexture;
	UPROPERTY(EditAnywhere)
	int32 ItemData_ItemPrice;
	UPROPERTY(EditAnywhere)
	FString ItemData_AttackType;
	UPROPERTY(EditAnywhere)
	float AttackDamage = 6.f;
	UPROPERTY(EditAnywhere)
	FName WeaponName;

	bool IsEquiped;
	bool bCasting;
	float CastingClock;
	float DamageScale;

	void Fire();
	void BuckShot();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
