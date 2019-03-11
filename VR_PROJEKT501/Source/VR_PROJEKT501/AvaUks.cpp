// Fill out your copyright notice in the Description page of Project Settings.

#include "AvaUks.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UAvaUks::UAvaUks()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAvaUks::BeginPlay()
{
	Super::BeginPlay();
	
	Omanik = GetOwner();
	ActorMisAvab = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UAvaUks::AvaUks()
{
	// Määra uksele pööraja
	Omanik->SetActorRotation(FRotator(0.0f, AvatudNurk, 0.0f));
}

void UAvaUks::SuleUks()
{
	// Määra uksele pööraja
	Omanik->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UAvaUks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Kui ActorMisAvab on volüümi sees, siis uks avaneb
	if (SurvePlaat->IsOverlappingActor(ActorMisAvab))
	{
		AvaUks();
		ViimaneAvatudUkseAeg = GetWorld()->GetTimeSeconds();
	}

	 // Kontroll, kas on aeg uks sulgeda
	if (GetWorld()->GetTimeSeconds() - ViimaneAvatudUkseAeg > UkseSulgumiseViide) {
		SuleUks();
	}

}

