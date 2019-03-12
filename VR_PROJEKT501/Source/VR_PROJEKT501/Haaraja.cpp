// Fill out your copyright notice in the Description page of Project Settings.

#include "Haaraja.h"
#include "DrawDebugHelpers.h"

#define VALJA


// Sets default values for this component's properties
UHaaraja::UHaaraja()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHaaraja::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Haaraja raporteerib valmidusest!"));
	
}


// Called every frame
void UHaaraja::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector MangijaVaatePunktiAsukoht;
	FRotator MangijaVaatePunktiRotatsioon;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		VALJA MangijaVaatePunktiAsukoht,
		VALJA MangijaVaatePunktiRotatsioon
	);
	//UE_LOG(LogTemp, Warning, TEXT("Asukoht %s, Rotatsioon %s"),
	//	*MangijaVaatePunktiAsukoht.ToString(),
	//	*MangijaVaatePunktiRotatsioon.ToString()
	//);

	UWorld* WorldContext = GetWorld();
	if (!WorldContext) {
		UE_LOG(LogTemp, Warning, TEXT("Pole maailma Context Available!"));
		return;

	}

	FVector JooneJaljeLopp = MangijaVaatePunktiAsukoht + MangijaVaatePunktiRotatsioon.Vector() * 100;
	// tombame punase joone et visualiseerida haarajat
	DrawDebugLine(
		GetWorld(),
		MangijaVaatePunktiAsukoht,
		JooneJaljeLopp,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f);
}

