// Fill out your copyright notice in the Description page of Project Settings.


#include "CStageGameMode.h"
#include "CGameInstance.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Particles/ParticleSystemComponent.h"

ACStageGameMode::ACStageGameMode() : Super()
{
	ConstructorHelpers::FObjectFinder<UDataTable> QuestTableFinder(TEXT("/Game/Resources/DataTables/DT_BattleField_QuestsTable"));
	if (QuestTableFinder.Succeeded())	QuestTable = QuestTableFinder.Object;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	TArray<AActor*> tempArr;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("DirectionalLight"), tempArr);
	if (tempArr.Num() <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("ERROR In ACStageGameMode : No Directional Light Found"));
	}
	for (AActor* A : tempArr)
	{
		if (ADirectionalLight* DL = Cast<ADirectionalLight>(A))
		{
			DirectionalLight = DL;
		}
	}

	PostProcessMaxRadius = 20000.f;
}

void ACStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	UMaterialParameterCollection* MPC = LoadObject<UMaterialParameterCollection>(nullptr, TEXT("/Game/Resources/Levels/Material/MPC_Outlines"));
	if (MPC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MPC_Outlines Can Not Found"));
		return;
	}
	MPC_GlobalPostProcessVolume = GetWorld()->GetParameterCollectionInstance(MPC);
	if (MPC_GlobalPostProcessVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MPC_GlobalPostProcessVolume Can Not Found"));
		return;
	}

	//SpawnedParticleComponents.Heapify();
}

void ACStageGameMode::Tick(float DeltaSeconds)
{
	if (DirectionalLight == nullptr) return;

// On Hour Per Sec
	//float TickTime = DeltaSeconds * MaxClock / FullDaySecond;
	//LevelClock += TickTime;
	//if (LevelClock > MaxClock) LevelClock -= MaxClock;

	//float Angle = 360.f / FullDaySecond * DeltaSeconds;
	//FQuat Rot = FQuat(FVector(0.f, 1.f, 0.f), FMath::DegreesToRadians(Angle));
	//DirectionalLight->AddActorLocalRotation(Rot);

	if (bPostProcessZoom)
	{
		if (PostProcessRadius <= 0.f) return;

		PostProcessRadius -= PostProcessMaxRadius * DeltaSeconds / 0.1f * PostProcessRadius / PostProcessMaxRadius;
		if (PostProcessRadius < 0.f)
		{
			PostProcessRadius = 0.f;
		}
		UpdateRadius(PostProcessRadius);
	}

	if (SpawnedParticleComponents.Num() > 0.f)
	{
		for (int i = 0; i < SpawnedParticleComponents.Num(); i++)
		{
			UE_LOG(LogTemp, Log, TEXT("ACStageGameMode Particles[%d] : %s\t%s\tLifeSpan : %f"),
				i, *SpawnedParticleComponents[i]->GetName(), SpawnedParticleComponents[i]->IsActive() ? TEXT("Active") : TEXT("False"), SpawnedParticleLifeSpans[i]
			);

			SpawnedParticleLifeSpans[i] -= DeltaSeconds;
			if (SpawnedParticleLifeSpans[i] < -30.f)
			{
				SpawnedParticleComponents[i]->DestroyComponent();
				SpawnedParticleComponents.RemoveAt(i);
				SpawnedParticleLifeSpans.RemoveAt(i);
			}
			else if (SpawnedParticleLifeSpans[i] < 0.f)
			{
				SpawnedParticleComponents[i]->Deactivate();
			}
		}
	}
}

FQuestsRow* ACStageGameMode::GetQuestbyIndex(int32 QuestIdx)
{
	return QuestTable->FindRow<FQuestsRow>(FName(FString::FormatAsNumber(QuestIdx)), FString(""));
}

void ACStageGameMode::InitLevelClock(float fClock)
{
	if (DirectionalLight == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("ACStageGameMode : DirectionalLight Not Found"));
		return;
	}

	float Angle = (FMath::Abs(LevelClock - fClock) / MaxClock) * 360.f;

	LevelClock = fClock;

	FQuat Rot = FQuat(FVector(0.f, 1.f, 0.f), FMath::DegreesToRadians(Angle));
	DirectionalLight->AddActorLocalRotation(Rot);
}

void ACStageGameMode::UpdatePlayerCharacterPos(FVector Pos)
{
	//PlayerCharacterPos = Pos;

	if (MPC_GlobalPostProcessVolume == nullptr) return;
	MPC_GlobalPostProcessVolume->SetVectorParameterValue("PlayerPos", Pos);
}

void ACStageGameMode::UpdateRadius(float e)
{
	if (MPC_GlobalPostProcessVolume == nullptr) return;
	MPC_GlobalPostProcessVolume->SetScalarParameterValue("Radius", e);
	UE_LOG(LogTemp, Log, TEXT("ACStageGameMode::UpdateRadius : %f"), e);
}

float ACStageGameMode::GetPostProcessRadius()
{
	return PostProcessRadius;
}

void ACStageGameMode::PostProcessZoom(bool IsStart, FVector ZoomPos)
{
	if (MPC_GlobalPostProcessVolume == nullptr) return;
	if (IsStart) MPC_GlobalPostProcessVolume->SetVectorParameterValue("PlayerPos", ZoomPos);
	MPC_GlobalPostProcessVolume->SetScalarParameterValue("IsDesaturate", IsStart ? 1.f : 0.f);

	bPostProcessZoom = IsStart;
	PostProcessRadius = PostProcessMaxRadius;
	//return PostProcessRadius;
}

void ACStageGameMode::ExecutePlayerDodgedEvent()
{
	PlayerDodged.ExecuteIfBound();
}

void ACStageGameMode::ExecutePlayerDodgedEndEvent()
{
	PlayerDodgedEnd.ExecuteIfBound();
	PostProcessZoom(false, FVector::ZeroVector);
}

void ACStageGameMode::SpawnParticle(UParticleSystem* SpawnParticle, float LifeSpan, FVector Location, FRotator Rotation, FVector Scale, USceneComponent* ToAttachComponent)
{
	if (SpawnParticle == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("ACStageGameMode::SpawnParticle SpawnParticle Not Found"));
		return;
	}
	//if (ToAttachComponent != nullptr)
	//{
	//	UGameplayStatics::SpawnEmitterAttached(SpawnParticle, ToAttachComponent, NAME_None, Location, Rotation);
	//	return;
	//}
	//Check If There's Usable(Currently Disabled) ParticleSystemComponent
	if (SpawnedParticleComponents.Num() > 0)
	{
		for (int i = 0; i < SpawnedParticleComponents.Num(); i++)
		{
			if (!SpawnedParticleComponents[i]->IsActive())
			{
				SpawnedParticleComponents[i]->SetTemplate(SpawnParticle);
				SpawnedParticleLifeSpans[i] = LifeSpan;
				SpawnedParticleComponents[i]->SetRelativeScale3D(Scale);
				if (ToAttachComponent != nullptr)
				{
					SpawnedParticleComponents[i]->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
					SpawnedParticleComponents[i]->AttachToComponent(ToAttachComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					//SpawnedParticleComponents[i]->SetRelativeLocation(Location);
					//SpawnedParticleComponents[i]->SetRelativeRotation(Rotation);
				}
				else
				{
					SpawnedParticleComponents[i]->SetWorldLocation(Location);
					SpawnedParticleComponents[i]->SetWorldRotation(Rotation);
				}
				SpawnedParticleComponents[i]->Activate();
				return;
			}
		}
	}
	// Create
	UParticleSystemComponent* PSC = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, Location, Rotation, false);
	PSC->SetRelativeScale3D(Scale);
	if (ToAttachComponent != nullptr)
	{
		PSC->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		PSC->AttachToComponent(ToAttachComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		PSC->SetRelativeLocation(Location);
		PSC->SetRelativeRotation(Rotation);
	}
	else
	{
		PSC->SetWorldLocation(Location);
		PSC->SetWorldRotation(Rotation);
	}
	SpawnedParticleComponents.Add(PSC);
	SpawnedParticleLifeSpans.Add(LifeSpan);
	UE_LOG(LogTemp, Log, TEXT("ACStageGameMode Spawn New Component"));
	return;
}
