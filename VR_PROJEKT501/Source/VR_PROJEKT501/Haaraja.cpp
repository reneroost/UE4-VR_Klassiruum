// Fill out your copyright notice in the Description page of Project Settings.

#include "Haaraja.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"

#define VALJA


// Sets default values for this component's properties
UHaaraja::UHaaraja()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Kutsutakse välja, kui mäng algab
void UHaaraja::BeginPlay()
{
	Super::BeginPlay();
	LeiaFyysikaKasitlejaKomponent();
	SeadistaSisendKomponent();
}

/// Otsi ühendatud füüsika käsitlejat (Physics Handle)
void UHaaraja::LeiaFyysikaKasitlejaKomponent() 
{
	// Otsi ühendatud füüsika käsitlejat
	FyysikaKasitleja = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (FyysikaKasitleja == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s puudu FyysikaKasitleja komponent"), *GetOwner()->GetName());
	}
}

/// Otsi yhendatud sisend komponenti (Input Component) (ilmub välja ainult mängu jooksmise ajal)
void UHaaraja::SeadistaSisendKomponent()
{
	SisendKomponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (SisendKomponent)
	{
		SisendKomponent->BindAction("Haara", IE_Pressed, this, &UHaaraja::Haara);
		SisendKomponent->BindAction("Haara", IE_Released, this, &UHaaraja::Vabasta);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s puudu sisendkomponent"), *GetOwner()->GetName());
	}
}


void UHaaraja::Haara() {
	// Järgi mängijast väljuvat kujutletavat joont ja vaata,
	// kas me ulatume mõne actor'ini millel on seadistatud physics body collision channel
	auto TabamuseVastus = SaaLahimUlatusesOlevFyysikaKeha();
	auto KomponentMidaHaarata = TabamuseVastus.GetComponent();
	auto ActorTabas = TabamuseVastus.GetActor();

	// Kui me tabame midagi, siis ühenda füüsika käsitleja (Physics Handle)
	if (ActorTabas != nullptr) {
		FyysikaKasitleja->GrabComponent(
			KomponentMidaHaarata,
			NAME_None,
			KomponentMidaHaarata->GetOwner()->GetActorLocation(),
			true // lubab pöörelda
		);
	}
}

void UHaaraja::Vabasta() {
	FyysikaKasitleja->ReleaseComponent();
}

// Kutsutakse välja iga kaader
void UHaaraja::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// kontroll, kas me oleme haaranud komponendi
	if (FyysikaKasitleja->GrabbedComponent) {
		// liigutab objekti mida me hoiame
		FyysikaKasitleja->SetTargetLocation(SaaVaatepuntkiJooneLopp());
	}
}

const FHitResult UHaaraja::SaaLahimUlatusesOlevFyysikaKeha()
{
	
	/// tõmbab punase silumisjoone et visualiseerida haarajat
/*	DrawDebugLine(
		GetWorld(),
		MangijaVaatePunktiAsukoht,
		JooneJaljeLopp,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f);*/

	/// Jälgi välja ulatuvat joont (line-trace) (AKA ray-cast)
	FHitResult TabamusTulemus;
	FCollisionQueryParams TraceParameetrid(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT TabamusTulemus,
		SaaVaatepuntkiJooneAlgus(),
		SaaVaatepuntkiJooneLopp(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameetrid
	);

	// Vaatab, mida me tabasime
	AActor* ActorPihtas = TabamusTulemus.GetActor();
	if (ActorPihtas) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace tabas: %s"), *(ActorPihtas->GetName()));
	} 
	return TabamusTulemus;
}

FVector UHaaraja::SaaVaatepuntkiJooneAlgus() {
	FVector MangijaVaatePunktiAsukoht;
	FRotator MangijaVaatePunktiRotatsioon;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		VALJA MangijaVaatePunktiAsukoht,
		VALJA MangijaVaatePunktiRotatsioon
	);
	return MangijaVaatePunktiAsukoht;
}

FVector UHaaraja::SaaVaatepuntkiJooneLopp() {
	FVector MangijaVaatePunktiAsukoht;
	FRotator MangijaVaatePunktiRotatsioon;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		VALJA MangijaVaatePunktiAsukoht,
		VALJA MangijaVaatePunktiRotatsioon
	);
	return MangijaVaatePunktiAsukoht + MangijaVaatePunktiRotatsioon.Vector() * 100;
}