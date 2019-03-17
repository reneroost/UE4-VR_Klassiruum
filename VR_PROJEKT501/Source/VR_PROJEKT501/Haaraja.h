// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Haaraja.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR_PROJEKT501_API UHaaraja : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHaaraja();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// kui kaugele mangija ette me ulatume sentimeetrites
	float Ulatus = 100.f;
	
	UPhysicsHandleComponent* FyysikaKasitleja = nullptr;

	UInputComponent* SisendKomponent = nullptr;

	// Ray-cast ja haara mis on haardeulatuses
	void Haara();

	// Kutsutakse, kui haare vabaneb
	void Vabasta();

	// Leia (eeldatavalt) ühendatud füüsika käsitleja
	void LeiaFyysikaKasitlejaKomponent();

	// Seadista üles (eeldatavalt) ühendatud sisendkomponent
	void SeadistaSisendKomponent();

	// Registreeri ulatuses oleva esimesena tabatud füüsilise keha
	const FHitResult SaaLahimUlatusesOlevFyysikaKeha();

	// Tagastab ulatusjoone praeguse alguspunkti
	FVector SaaVaatepuntkiJooneAlgus();

	// Tagastab ulatusjoone praeguse lõpppunkti
	FVector SaaVaatepuntkiJooneLopp();
};
