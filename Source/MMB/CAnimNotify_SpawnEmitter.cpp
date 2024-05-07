// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_SpawnEmitter.h"
#include "PCH.h"

void UCAnimNotify_SpawnEmitter::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GetPlayerCharacter(MeshComp);
	/*UStaticMeshSocket* FireSocket = StaticMeshComponent->GetStaticMesh()->FindSocket("FireSocket");
	FVector StartLocation = GetActorLocation() + GetActorRotation().RotateVector(FireSocket->RelativeLocation);*/
}

bool UCAnimNotify_SpawnEmitter::GetPlayerCharacter(USkeletalMeshComponent* MeshComp)
{
	PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (PC == nullptr) return false;
	WP = PC->WeaponEquipped;
	IIWeapon* Weapon = Cast<IIWeapon>(WP);
	if (Weapon == nullptr) return false;
	//UStaticMesh* SM = WP->StaticMeshComponent->GetStaticMesh();
	//UStaticMeshSocket* FireSocket = SM->FindSocket("FireSocket");
	//UStaticMeshSocket* FireSocket = WP->GetSocket("FireSocket");

	Weapon->GetSocketTransform(FireSocketTransform, "FireSocket");
	//FireSocket->GetSocketTransform(FireSocketTransform, WP->GetStaticMeshComponent());
	return (PC != nullptr) ? true : false;
}