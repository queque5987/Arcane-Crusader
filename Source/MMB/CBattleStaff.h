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
	//virtual void LMB_Attack() override;
	virtual void LMB_Triggered(struct AttackResult& AttackResult) override;
	virtual void LMB_Completed(struct AttackResult& AttackResult) override;
	virtual void RMB_Triggered(struct AttackResult& AttackResult) override;


	//void LMB_Triggered(struct AttackResult& AttackResult);
	//void LMB_Completed(struct AttackResult& AttackResult);
	//void RMB_Triggered(struct AttackResult& AttackResult);
	//virtual void ComboContinue() override;
	//virtual void RMB_Completed() override;

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

	UFUNCTION()
	void OnPickUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/*typedef void (ACBattleStaff::* CallBackFunction)(ACPlayerCharacter*);
	CallBackFunction FComboContinue;*/

	virtual void SpawnEmitterAttachedToSocket() override;
	//void SpawnEmitterAttachedToSocket();


	class UParticleSystem* ParticleSystemExplode;

	virtual void Tick(float DeltaTime) override;
	class UParticleSystemComponent* FireSocketEffectComponent;

	virtual bool MeleeAttackHitCheck() override;

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
	TQueue<class UParticleSystemComponent*> HitParticleQueue;
	void DequeueHitParticle();
private:
	float AttackingEffectClock = 2.4f;
	float CAEC = 0.f;
	//class UParticleSystemComponent* ParticleSystemFireBall;
	void CreateParticleSystem();
	//void Combo1Attack(ACPlayerCharacter* PC);
	//void Combo2Attack(ACPlayerCharacter* PC);
	//void Combo3Attack(ACPlayerCharacter* PC);







public:
	class UStaticMeshComponent* StaticMeshComponent;
	class USphereComponent* Collider;

	TArray<UParticleSystem*> WeaponEffect;
	TArray<USoundBase*> WeaponSoundEffect;
	class USoundCue* StaffMeleeHitSoundCue;
protected:
	float tempDamage0;
	float tempDamage1;
	float tempDamage2;
	float RequiredStamina;

	FName WeaponMesh;

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
