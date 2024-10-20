#include "CEnemy_Nightmare.h"
#include "CEnemyAIController_NM.h"
#include "Materials/Material.h"

ACEnemy_Nightmare::ACEnemy_Nightmare() : Super()
{
	//check(IsInGameThread());

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SMFinder(TEXT("/Game/FourEvilDragonsHP/Meshes/DragonTheNightmare/DragonTheNightmareSK"));

	if (SMFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SMFinder.Object);
		GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		
		FString MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheNightmare/AlbinoMat_Inst");
		switch (FMath::RandRange(0, 3))
		{
		case(0):
			break;
		case(1):
			MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheNightmare/DarkBlueMat_Inst");
			break;
		case(2):
			MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheNightmare/GreenMat_Inst");
			break;
		case(3):
			MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheNightmare/RedMat_Inst");
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
	AIControllerClass = ACEnemyAIController_NM::StaticClass();
}

void ACEnemy_Nightmare::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FString AnimBPAdderss = "Class'/Game/Enemy/NightMare/Animation/BP_EnemyAnimIntance.BP_EnemyAnimIntance_C'";
	UClass* tempAnimBP = LoadObject<UClass>(nullptr, *AnimBPAdderss);
	if (!tempAnimBP) return;
	GetMesh()->SetAnimInstanceClass(tempAnimBP);
}
