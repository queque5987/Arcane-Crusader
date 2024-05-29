// Fill out your copyright notice in the Description page of Project Settings.


#include "CWeapon.h"

ACWeapon::ACWeapon() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));
	Collider->SetupAttachment(StaticMeshComponent);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	SetActorRelativeRotation(FRotator(0.f, 0.f, -75.f));
	SetActorRelativeLocation(FVector(0.f, 0.f, 150.f));

	SetActorEnableCollision(true);

	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	WeaponEffect.SetNum(MAX_E_WEAPONEFFECT);
}

void ACWeapon::SetIsEquiped(bool e)
{
	IsEquiped = e;
	if (e)
	{
		Collider->OnComponentBeginOverlap.RemoveDynamic(this, &ACWeapon::OnOverlapBegin);
	}
	else
	{
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ACWeapon::OnOverlapBegin);
	}
}

bool ACWeapon::MeleeAttackHitCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, GetAttachParentActor());
	//FCollisionObjectQueryParams OQP(ECollisionChannel::ECC_Pawn);
	FCollisionObjectQueryParams OQP(PlayerAttackChannel);
	//FVector FireSocketLocation = 
	FTransform FireSocketTransform;
	UStaticMesh* SM = StaticMeshComponent->GetStaticMesh();
	UStaticMeshSocket* FireSocket = SM->FindSocket("FireSocket");
	FireSocket->GetSocketTransform(FireSocketTransform, StaticMeshComponent);

	/*bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		FireSocketTransform.GetLocation(),
		FireSocketTransform.GetLocation(),
		FQuat::Identity,
		PlayerAttackChannel,
		FCollisionShape::MakeSphere(30.f),
		Params
	);*/

	bool bResult = GetWorld()->SweepSingleByObjectType(
		HitResult,
		FireSocketTransform.GetLocation(),
		FireSocketTransform.GetLocation(),
		FQuat::Identity,
		OQP,
		FCollisionShape::MakeSphere(30.f),
		Params
	);
	//if (bResult) UE_LOG(LogTemp, Log, TEXT("Hit At Actor : %s"), *HitResult.GetActor()->GetName());
	//if (bResult) UE_LOG(LogTemp, Log, TEXT("Hit At Component : %s"), *HitResult.GetComponent()->GetFullName());
	//if (bResult) UE_LOG(LogTemp, Log, TEXT("Hit At Actor : %s"), *HitResult.GetActor()->GetFullName());

	if (bResult)
	{
		ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(HitResult.GetActor());
		if (EC == nullptr) return false;
		ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetAttachParentActor());
		if (PC == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("AttachParentActor is not ACPlayerCharacter"));
			return false;
		}
		UE_LOG(LogTemp, Log, TEXT("Attack Damage : %f, Damage Scale : %f"), AttackDamage, DamageScale);

		EC->HitDamage(AttackDamage * DamageScale, *PC, HitResult.Location);
	}
	
	return bResult;
}

void ACWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACPlayerCharacter* PlayerCharacter = Cast<ACPlayerCharacter>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("On Overlap Begin... Other Actor Name: %s"), *OtherActor->GetName()));
		ACPlayerController* PCC = Cast<ACPlayerController>(PlayerCharacter->GetController());
		PCC->AddInventoryItem(GetItemData(PlayerCharacter));
		this->Destroy();
		//return;
		//IsEquiped = true;
		//SetActorRelativeRotation(FRotator::ZeroRotator);
		//PlayerCharacter->Equip(*this);
		//Collider->OnComponentBeginOverlap.RemoveDynamic(this, &ACWeapon::OnOverlapBegin);
	}
}

UCInventoryItemData* ACWeapon::GetItemData(ACharacter* PC)
{
	UCInventoryItemData* ID = NewObject<UCInventoryItemData>(PC, UCInventoryItemData::StaticClass(), WeaponName);
	ID->SetIconTexture(ItemData_IconTexture);
	ID->SetPrice(ItemData_ItemPrice);
	//ID->SetAttackType(ItemData_AttackType);
	ID->SetItemType(0);
	ID->SetAttackDamage(AttackDamage);
	ID->SetstrName(WeaponName.ToString());
	return ID;
}

// Called every frame
void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsEquiped)
	{
		SetActorRotation(GetActorRotation() + FRotator(0.f, 3.f, 0.f));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Rotation: %s"), *GetActorRotation().ToString()));
}

