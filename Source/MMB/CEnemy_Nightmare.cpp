// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_Nightmare.h"
#include "CEnemyAIController_NM.h"
#include "Materials/Material.h"

ACEnemy_Nightmare::ACEnemy_Nightmare() : Super()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SMFinder(TEXT("/Game/FourEvilDragonsHP/Meshes/DragonTheNightmare/DragonTheNightmareSK.DragonTheNightmareSK"));
	ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBPFinder(TEXT("/Game/Enemy/NightMare/Animation/BP_EnemyAnimIntance.BP_EnemyAnimIntance"));
	
	if (SMFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SMFinder.Object);
		GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		
		FString MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheNightmare/AlbinoMat_Inst.AlbinoMat_Inst");
		switch (FMath::RandRange(0, 3))
		{
		case(0):
			break;
		case(1):
			MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheNightmare/DarkBlueMat_Inst.DarkBlueMat_Inst");
			break;
		case(2):
			MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheNightmare/GreenMat_Inst.GreenMat_Inst");
			break;
		case(3):
			MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheNightmare/RedMat_Inst.RedMat_Inst");
			break;
		default:
			break;
		}
		ConstructorHelpers::FObjectFinder<UMaterialInstance> Mat0Finder(*MatAddres);
		if (Mat0Finder.Succeeded()) 
		{
			GetMesh()->SetMaterial(0, Mat0Finder.Object);
		}
	}
	if (AnimBPFinder.Succeeded()) GetMesh()->SetAnimClass(AnimBPFinder.Object->GeneratedClass);
	AIControllerClass = ACEnemyAIController_NM::StaticClass();
}
