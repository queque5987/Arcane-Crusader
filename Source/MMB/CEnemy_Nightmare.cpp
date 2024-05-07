// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_Nightmare.h"
#include "CEnemyAIController_NM.h"

ACEnemy_Nightmare::ACEnemy_Nightmare() : Super()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SMFinder(TEXT("/Game/FourEvilDragonsHP/Meshes/DragonTheNightmare/DragonTheNightmareSK.DragonTheNightmareSK"));
	ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBPFinder(TEXT("/Game/Enemy/NightMare/Animation/BP_EnemyAnimIntance.BP_EnemyAnimIntance"));
	if (SMFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SMFinder.Object);
		GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	}
	if (AnimBPFinder.Succeeded()) GetMesh()->SetAnimClass(AnimBPFinder.Object->GeneratedClass);
	AIControllerClass = ACEnemyAIController_NM::StaticClass();
}
