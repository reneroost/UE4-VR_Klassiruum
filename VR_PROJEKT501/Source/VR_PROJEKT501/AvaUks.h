// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "AvaUks.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUkseSundmus);

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FUkseSundmus OnAva;

	UPROPERTY(BlueprintAssignable)
	FUkseSundmus OnSule;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* SurvePlaat = nullptr;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 20.f;

	AActor* Omanik = nullptr;			// Uks

	// Tagastab kogumassi kilogrammides
	float SaaSurvePlaadilOlevateObjektideKogumass();
};
