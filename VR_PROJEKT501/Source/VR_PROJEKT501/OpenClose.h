// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenClose.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR_PROJEKT501_API UOpenClose : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenClose();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* Owner = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Et saaks seda parameetrit UE-s muuta
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(VisibleAnywhere)
	float openAngle = 85.f;

	UPROPERTY(VisibleAnywhere)
	AActor* ActorThatOpens;

	void OpenDoor();
	void CloseDoor();
	
};
