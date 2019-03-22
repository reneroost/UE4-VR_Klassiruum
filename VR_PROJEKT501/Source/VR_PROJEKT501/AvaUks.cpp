// Fill out your copyright notice in the Description page of Project Settings.

#include "AvaUks.h"
#include "GameFramework/Actor.h"

#define OUT


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

	if (!SurvePlaat) {
		UE_LOG(LogTemp, Error, TEXT("%s puudu surveplaat"), *GetOwner()->GetName());
	}
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

	if (SaaSurvePlaadilOlevateObjektideKogumass() > 20.f)
	{
		AvaUks();
		ViimaneAvatudUkseAeg = GetWorld()->GetTimeSeconds();
	}

	 // Kontroll, kas on aeg uks sulgeda
	if (GetWorld()->GetTimeSeconds() - ViimaneAvatudUkseAeg > UkseSulgumiseViide)
	{
		SuleUks();
	}
}

float UAvaUks::SaaSurvePlaadilOlevateObjektideKogumass()
{

	float KoguMass = 0.f;

	// Leiab kõik surveplaadil olevad actorid
	TArray<AActor*> SurvePlaadilOlevadActorid;

	if (!SurvePlaat) { return KoguMass; }
	SurvePlaat->GetOverlappingActors(OUT SurvePlaadilOlevadActorid);

	// Liidab nende massid kokku
	for (const auto* Actor : SurvePlaadilOlevadActorid)
	{
		KoguMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on surveplaadil"), *Actor->GetName());
	}

	return KoguMass;
}

