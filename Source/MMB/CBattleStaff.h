// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWeapon.h"
#include "CWeapon.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "CBattleStaff.generated.h"

UCLASS()
class MMB_API ACBattleStaff : public AActor, public IIWeapon
{
	GENERATED_BODY()
public:
	ACBattleStaff();

	virtual void BeginPlay() override;
	//virtual void LMB_Attack() override;
	virtual void LMB_Triggered(struct AttackResult& AttackResult) override;
	virtual void LMB_Completed(struct AttackResult& AttackResult) override;
	virtual void RMB_Triggered(struct AttackResult& AttackResult) override;
	virtual void RMB_Completed(struct AttackResult& AttackResult) override;

	//void LMB_Triggered(struct AttackResult& AttackResult);
	//void LMB_Completed(struct AttackResult& AttackResult);
	//void RMB_Triggered(struct AttackResult& AttackResult);
	virtual void Tab_Triggered(struct AttackResult& AttackResult) override;
	//virtual void ComboContinue() override;
	//virtual void RMB_Completed() override;
	virtual void Ult_Triggered(struct AttackResult& AttackResult) override;
	virtual void UltFunc0() override;
	virtual void UltFunc1() override;

	virtual void OnEquipped() override;
	//virtual void OnUnequipped() override;

	virtual float GettempDamage0() override;
	virtual float GettempDamage1() override;
	virtual float GettempDamage2() override;
	//float GettempDamage0();
	//float GettempDamage1();
	//float GettempDamage2();

	//void SetIsEquiped(bool e);
	virtual void SetIsEquiped(bool e) override;
	virtual void SetAttackDamage(float e) override { AttackDamage = e; }
	virtual void SetWeaponName(FName e) override { WeaponName = e; }
	virtual void OnAttackSwingEnd() override;

	virtual class UStaticMeshComponent* GetStaffStaticMeshComponent() override;

	UFUNCTION()
	void OnPickUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/*typedef void (ACBattleStaff::* CallBackFunction)(ACPlayerCharacter*);
	CallBackFunction FComboContinue;*/

	virtual int32 GetWeaponMode() override;

	virtual void SpawnEmitterAttachedToSocket() override;
	//void SpawnEmitterAttachedToSocket();


	class UParticleSystem* ParticleSystemExplode;

	virtual void Tick(float DeltaTime) override;
	class UParticleSystemComponent* FireSocketEffectComponent;

	virtual bool MeleeAttackHitCheck(int32 HitMode = 0, float fDamageScale = 0.f) override;

	virtual class UParticleSystem* GetWeaponEffect(int e) override;
	virtual class USoundBase* GetWeaponSoundEffect(int e) override;
	virtual TArray<class UParticleSystem*>* GetWeaponEffect() override;
	virtual class UStaticMeshSocket* GetSocket(FName e) override;
	virtual class UStaticMeshComponent* GetStaticMeshComponent() override;
	virtual void GetSocketTransform(FTransform& SocketTransform, FName SocketName) override;
protected:
	virtual class UCInventoryItemData* GetItemData(ACharacter* PC) override;
	//class UCInventoryItemData* GetItemData(ACharacter* PC);
	UStaticMeshSocket* FireSocket;
	FVector PrevFireSocketPos;
	FVector SwingingDirection;
	FTimerHandle EffectSpawnTimerHandler;
	FTimerHandle ComboAttackResetTimerHandler;
	TQueue<class UParticleSystemComponent*> HitParticleQueue;
	void DequeueHitParticle();
private:
//HitCheck
	bool StaffHitCheck(FVector HitLocation = FVector::ZeroVector, float fDamageScale = 0.f);
	bool FistHitCheck(bool IsLeft, float fDamageScale = 0.f);

	float AttackingEffectClock = 2.4f;
	//float CAEC = 0.f; ????

	// ??
	void CreateParticleSystem();

// Brute Mode
	bool BruteMode;
	float BruteCoolDownMax;
	float BruteCoolDown;
	float BruteGaugeMax;
	float BruteGauge;
	float BruteChargedAD;
	int32 BruteLMBComboStack;
	void AbortBruteMode();
public:
	bool GetBruteMode() { return BruteMode; };
	float GetBruteCoolDownMax() { return BruteCoolDownMax; };
	float GetBruteCoolDown() { return BruteCoolDown; };
	float GetBruteGaugeMax() { return BruteGaugeMax; };
	float GetBruteGauge() { return BruteGauge; };
	virtual void AddBruteGauge(float BG) override;
// Brute Mode End
public:
	class UStaticMeshComponent* StaticMeshComponent;
	class USphereComponent* Collider;

// Weapon Effect
	UPROPERTY(EditAnywhere)
	class UCWeaponSilhouetteComponent* WeaponOraEffect;
	UPROPERTY(EditAnywhere)
	class UCWeaponSilhouette_Gauntlet* WeaponOraEffect_BruteMode;

	TArray<UParticleSystem*> WeaponEffect;
	TArray<USoundBase*> WeaponSoundEffect;
	class USoundCue* StaffMeleeHitSoundCue;

	virtual void ActivateEffect() override;
	virtual void DeactivateEffect() override;
	virtual void SetCharge(float e, bool IsLeft = false) override;
protected:
	float tempDamage0;
	float tempDamage1;
	float tempDamage2;
	float RequiredStamina;

	FName WeaponMesh;

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
	float AttackDamage;
	UPROPERTY(EditAnywhere)
	FName WeaponName;

	bool IsEquiped;
	bool bCasting;
	float CastingClock;
	float DamageScale;
};
