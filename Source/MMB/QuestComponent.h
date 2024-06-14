// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMB_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestComponent();

protected:
	virtual void BeginPlay() override;
	void Quest0();
	void Quest1();
	//void Quest2();
	void Quest3();
	void Init_Quest0();
	void Init_Quest1();
	void Init_Quest2();
	void Init_Quest3();
	void Init_Quest4();

	void Init_Quest5();
	void Init_Quest6();
private:
	//Deprecated 20240531 Editor Only Function
	AActor* FindActorByLabel(TSubclassOf<AActor> FindClass, FString Label);
	AActor* FindActorByTag(TSubclassOf<AActor> FindClass, FName Tag);
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnQuestCleared(int RewardIndex);
	void OnQuestInitialize(int InitIndex);
		
};
