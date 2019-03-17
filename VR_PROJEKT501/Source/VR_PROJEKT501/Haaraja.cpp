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
	if (FyysikaKasitleja)
	{
		// füüsika käsitleja leiti
	}
	else
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
		UE_LOG(LogTemp, Warning, TEXT("Sisendkomponent leitud"));

		/// Seo sisendtelg
		SisendKomponent->BindAction("Haara", IE_Pressed, this, &UHaaraja::Haara);
		SisendKomponent->BindAction("Haara", IE_Released, this, &UHaaraja::Vabasta);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s puudu sisendkomponent"), *GetOwner()->GetName());
	}
}


void UHaaraja::Haara() {
	UE_LOG(LogTemp, Warning, TEXT("Haara vajutatud"));

	// Järgi mängijast väljuvat kujutletavat joont ja vaata,
	// kas me ulatume mõne actor'ini millel on seadistatud physics body collision channel
	auto TabamuseVastus = SaaLahimUlatusesOlevFyysikaKeha();
	auto ComponentToGrab = TabamuseVastus.GetComponent();
	auto ActorTabas = TabamuseVastus.GetActor();

	// Kui me tabame midagi, siis ühenda füüsika käsitleja (Physics Handle)
	if (ActorTabas != nullptr) {
		// ühendab füüsika käsitleja
		FyysikaKasitleja->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true // lubab pöörelda
		);
	}
}

void UHaaraja::Vabasta() {
	UE_LOG(LogTemp, Warning, TEXT("Haara vabastatud"));
	FyysikaKasitleja->ReleaseComponent();
}

// Kutsutakse välja iga kaader
void UHaaraja::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Saa mängija vaatepunkt
	FVector MangijaVaatePunktiAsukoht;
	FRotator MangijaVaatePunktiRotatsioon;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		VALJA MangijaVaatePunktiAsukoht,
		VALJA MangijaVaatePunktiRotatsioon
	);
	FVector JooneJaljeLopp = MangijaVaatePunktiAsukoht + MangijaVaatePunktiRotatsioon.Vector() * 100;


	// kontroll, kas me oleme haaranud komponendi
	if (FyysikaKasitleja->GrabbedComponent) {
		// liigutab objekti mida me hoiame
		FyysikaKasitleja->SetTargetLocation(JooneJaljeLopp);
	}
}

const FHitResult UHaaraja::SaaLahimUlatusesOlevFyysikaKeha()
{
	// Saa mängija vaatepunkt
	FVector MangijaVaatePunktiAsukoht;
	FRotator MangijaVaatePunktiRotatsioon;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		VALJA MangijaVaatePunktiAsukoht,
		VALJA MangijaVaatePunktiRotatsioon
	);
	FVector JooneJaljeLopp = MangijaVaatePunktiAsukoht + MangijaVaatePunktiRotatsioon.Vector() * 100;
	
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

	/// Seadista päringu parameetrid
	FCollisionQueryParams TraceParameetrid(FName(TEXT("")), false, GetOwner());

	/// Jälgi välja ulatuvat joont (line-trace) (AKA ray-cast)
	FHitResult Tabamus;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Tabamus,
		MangijaVaatePunktiAsukoht,
		JooneJaljeLopp,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameetrid
	);

	// Vaatab, mida me tabasime
	AActor* ActorPihtas = Tabamus.GetActor();
	if (ActorPihtas) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace tabas: %s"), *(ActorPihtas->GetName()));
	} 
	return Tabamus;
}
