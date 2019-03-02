// Fill out your copyright notice in the Description page of Project Settings.

#include "PositsioonistTeataja.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositsioonistTeataja::UPositsioonistTeataja()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPositsioonistTeataja::BeginPlay()
{
	Super::BeginPlay();

	FString ObjektiNimi = GetOwner()->GetName();
	FString ObjektiPositsioon = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s on positsioonil %s"), *ObjektiNimi, *ObjektiPositsioon);

}


// Called every frame
void UPositsioonistTeataja::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

