#include "CAnimNotifyState_EnemyTurn.h"
#include "IEnemyStateManager.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

void UCAnimNotifyState_EnemyTurn::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	TotalClock = TotalDuration;
	ElipsedTime = 0.f;
	ESM = Cast<IIEnemyStateManager>(MeshComp->GetOwner());
	Owner = MeshComp->GetOwner();
	if (ESM == nullptr || Owner == nullptr) return;
	TurnDestinationCharacter = ESM->GetDealingPlayer();
	InitRotation = Owner->GetActorRotation();
}

void UCAnimNotifyState_EnemyTurn::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	ElipsedTime += FrameDeltaTime;

	if (Owner == nullptr) return;
	if (TurnDestinationCharacter == nullptr) return;
	if (ElipsedTime < TotalClock / 2.f) TurnDestination = TurnDestinationCharacter->GetActorLocation();

	FRotator DestinedRot = UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), TurnDestination);
	DestinedRot.Roll = InitRotation.Roll;
	DestinedRot.Pitch = InitRotation.Pitch;
	Owner->SetActorRotation(FMath::Lerp(InitRotation, DestinedRot, ElipsedTime / TotalClock));
	//FVector Direction = (TurnDestination - Owner->GetActorLocation()).GetSafeNormal();

	//DrawDebugLine(GetWorld(), Owner->GetActorLocation(), Owner->GetActorLocation() + Owner->GetActorForwardVector() * 500.f, FColor::Red, false, -1.f, 0U, 30.f);
	//DrawDebugLine(GetWorld(), Owner->GetActorLocation(), Owner->GetActorLocation() + Direction * 500.f, FColor::Green, false, -1.f, 0U, 30.f);

	//double Theta = FMath::Acos(FVector::DotProduct(Owner->GetActorForwardVector(), Direction));
	//double YawToAdd = FMath::RadiansToDegrees(Theta);

	//UE_LOG(LogTemp, Log, TEXT("Turn Anim Notify : Theta : %f, Yaw:  %f"), Theta, YawToAdd);

	//FRotator DestinedRotation = Owner->GetActorRotation() + FRotator(0.f, YawToAdd, 0.f);
	//Owner->SetActorRotation(FMath::Lerp(InitRotation, DestinedRotation, ElipsedTime / TotalClock));
	//Owner->SetActorRotation(Owner->GetActorRotation() + FRotator(0.f, YawToAdd * (ElipsedTime / TotalClock), 0.f));

}

void UCAnimNotifyState_EnemyTurn::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
