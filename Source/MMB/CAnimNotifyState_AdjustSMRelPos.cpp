// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_AdjustSMRelPos.h"
#include "CPlayerCharacter.h"

void UCAnimNotifyState_AdjustSMRelPos::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!IsValid(PC)) return;
	FVector SpineLocation = PC->GetMesh()->GetBoneLocation("Spine");
	FVector ActorLocation = PC->GetActorLocation();

	FVector SpineLocWoZ = FVector(SpineLocation.X, SpineLocation.Y, 0.f);
	FVector ActorLocWoZ = FVector(ActorLocation.X, ActorLocation.Y, 0.f);

	Weights = ActorLocWoZ- SpineLocWoZ;
}

void UCAnimNotifyState_AdjustSMRelPos::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (!IsValid(PC)) return;
	//FVector SpineLocation = PC->GetMesh()->GetBoneLocation("Spine");
	//FVector ActorLocation = PC->GetActorLocation();
	FVector ActorLocation = PC->GetActorTransform().GetLocation();
	FVector SpineLocation = ActorLocation + PC->GetMesh()->GetBoneLocation("Spine");

	FVector SpineLocWoZ = FVector(SpineLocation.X, SpineLocation.Y, 0.f);
	FVector ActorLocWoZ = FVector(ActorLocation.X, ActorLocation.Y, 0.f);

	DrawDebugSphere(GetWorld(), SpineLocation, 50.f, 32, FColor::Red, false, 2.f);
	DrawDebugSphere(GetWorld(), ActorLocation, 50.f, 32, FColor::Green, false, 2.f);
	DrawDebugLine(GetWorld(), SpineLocation, ActorLocation, FColor::Green, false, 2.f);

	//GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -87.f), FRotator(0.f, -90.f, 0.f));
	//FVector Adjust = SpineLocWoZ - ActorLocWoZ;

	//PC->GetMesh()->SetRelativeLocation(Adjust);
	//UE_LOG(LogTemp, Log, TEXT("Spine : %s\n\tCollider : %s"), *SpineLocation.ToString(), *ActorLocation.ToString());
}

void UCAnimNotifyState_AdjustSMRelPos::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!IsValid(PC)) return;
	//PC->GetMesh()->SetRelativeLocation(FVector::ZeroVector);
}
