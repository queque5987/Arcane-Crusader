// Fill out your copyright notice in the Description page of Project Settings.


#include "CMeteor.h"

//ACMeteor::ACMeteor() :ACProjectile()
//{
//	ParticleSystemFireBall->SetWorldScale3D(FVector(3.f, 3.f, 3.f));
//	ParticleSystemFireBall->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));
//	
//	ConstructorHelpers::FObjectFinder<UParticleSystem> ExplodeFinder(TEXT("/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_GolemBot/Impact/P_Meteor_Impact_01.P_Meteor_Impact_01"));
//	if (ExplodeFinder.Succeeded()) ParticleSystemExplode->SetTemplate(ExplodeFinder.Object);
//}

//void ACMeteor::Tick(float DeltaTime)
//{
//	if (Trail == 0.f)
//	{
//		return;
//	}
//	ElipsedTime += DeltaTime;
//	FVector CurrentLocation = GetActorLocation();
//	FVector DirectionVector = -GetActorUpVector();
//
//	SetActorLocation(CurrentLocation + DirectionVector * Acceleration);
//	Trail -= (DirectionVector * Acceleration).Size();
//	if (Trail <= 0.f)
//	{
//		Explode(true);
//		Trail = 0.f;
//	}
//}
