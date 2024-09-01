// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWeapon.h"
#include "GameFramework/Actor.h"
#include "CRifleStaff.generated.h"

DECLARE_DELEGATE_OneParam(FBulletCountUpdated, float);

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
	class USoundCue* BombSoundCue;

	UPROPERTY(EditAnywhere)
	class UCWeaponSilhouette_Rifle* RifleOraEffect;

	class UParticleSystemComponent* FireSocketEffectComponent;
	virtual void LMB_Triggered(struct AttackResult& AttackResult) override;
	virtual void LMB_Completed(struct AttackResult& AttackResult) override;
	virtual void RMB_Triggered(struct AttackResult& AttackResult) override;
	virtual void RMB_Completed(struct AttackResult& AttackResult) override;
	virtual void Tab_Triggered(struct AttackResult& AttackResult) override;
	virtual void Ult_Triggered(struct AttackResult& AttackResult) override;

	virtual void UltFunc0() override;
	virtual void UltFunc1() override;
	/*Use Thie Instead Get BulletType*/
	virtual int32 GetWeaponMode() override { return BulletType; };
	virtual void SetIsEquiped(bool e) override;
	virtual void SetAttackDamage(float e) override { AttackDamage = e; }
	virtual void SetBulletType(int32 e) override;
	virtual void SetItemStat(struct ItemStat* ItemStats) override;
	virtual void SetWeaponName(FName e) override { WeaponName = e; }
	virtual void SetOwner(AActor* NewOwner) override;

	//virtual int32 GetCurrBulletType() override { return BulletType; }
	virtual float GetMaxBullet(int32 ToGetBulletType = 3) override;
	virtual float GetCurrBullet(int32 ToGetBulletType = 3) override;

protected:
	FRotator DefaultRotator;

	class ACRifleStaffBeacon* UltBeacon;

	virtual void BeginPlay() override;


	//Bullet Stat
	struct ItemStat* ItemStatus;

	TArray<float> MaxBullet;
	TArray<float> CurrBullet;

	int32 BulletType;
	float AttackRange = 2500.f;
	float BulletSpeed = 100.f;
	float ConstAttackCoolDown = 0.8f;
	//

	float LMBCharge = 0.f;
	int32 ChargeSoundFX = 0;
	TArray<FTimerHandle> MachineGunTimerHandler;
	FTimerHandle BulletChangeTimerHandler;
	FTimerHandle UltBombTimerHandler;
	int32 BombCounter;

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
	float fSpinAct;
	float CastingClock;
	float DamageScale;

	void Fire();
	void BuckShot(int32 i = 0);
	void CancleFire();
	bool SetSpendBullet(int32 Type, float Amount);

	bool HitCheckAtLocation(FVector SweepLocation, float Radius, float OverrideDamageScale);
public:
	FBulletCountUpdated BulletCountUpdated;

	void GetLeftBullet(FVector& LeftBulletPercent);
	class UAudioComponent* ChargeAudio;
	bool LMBLock = false;
	virtual void Tick(float DeltaTime) override;
	void SetLMBLock(bool e);
	/*Use Virtual Function - This Will Be Deprecated*/
	int32 GetBulletType() { return BulletType; };
	float GetLMBCharge() { return LMBCharge; }
	virtual void UpdateCharacterStat() override;

	virtual void UltBombArea(FVector BombLocation, float Radius) override;
};
