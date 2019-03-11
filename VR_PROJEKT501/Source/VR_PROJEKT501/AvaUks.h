// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "AvaUks.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR_PROJEKT501_API UAvaUks : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAvaUks();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void AvaUks();
	void SuleUks();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere)
	float AvatudNurk = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* SurvePlaat;

	UPROPERTY(EditAnywhere)
	float UkseSulgumiseViide = 1.f;

	float ViimaneAvatudUkseAeg;

	AActor* ActorMisAvab;		// Pawn pärineb actorist
	AActor* Omanik;				// Uks
};
