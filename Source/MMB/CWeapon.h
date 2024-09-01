
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCH.h"
#include "IWeapon.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "CWeapon.generated.h"

UCLASS()
class MMB_API ACWeapon : public AActor, public IIWeapon
{
	GENERATED_BODY()

public:	
	ACWeapon();
	class UStaticMeshComponent* StaticMeshComponent;
	class USphereComponent* Collider;


	virtual bool GetIsEquiped() override { return IsEquiped; }
	virtual void SetIsEquiped(bool e) override;

	virtual void LMB_Attack() override {}
	virtual void LMB_Triggered(struct AttackResult& AttackResult) override {}
	virtual void LMB_Completed(struct AttackResult& AttackResult) override {}
	virtual void RMB_Triggered(struct AttackResult& AttackResult) override {}
	virtual void RMB_Completed(struct AttackResult& AttackResult) override {}
	//virtual bool MeleeAttackHitCheck(int32 HitMode = 0) override;
	virtual void SpawnEmitterAttachedToSocket() override {};


	TArray<UParticleSystem*> WeaponEffect;
//protected:
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
	float AttackDamage = 1;
	UPROPERTY(EditAnywhere)
	FName WeaponName;

	bool IsEquiped;
	bool bCasting;
	float CastingClock;
	float DamageScale;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual class UCInventoryItemData* GetItemData(ACharacter* PC) override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetAttackDamage(float e) override { AttackDamage = e; }
	float GetAttackDamage() override { return AttackDamage; }
	void SetWeaponName(FName e) override { WeaponName = e; }
	FName GetWeaponName() override { return WeaponName; }

	//BattleStaff Combo1 Projectile Dmage
	virtual float GettempDamage0() override { return 0.f; };
	//BattleStaff Combo2 Projectile Dmage 
	virtual float GettempDamage1() override { return 0.f; };
	//BattleStaff Combo2 Explode Dmage 
	virtual float GettempDamage2() override { return 0.f; };
	virtual float GetRequiredStamina() override { return RequiredStamina; }
	virtual void SetRequiredStamina(float e) override { RequiredStamina = e; }
};
