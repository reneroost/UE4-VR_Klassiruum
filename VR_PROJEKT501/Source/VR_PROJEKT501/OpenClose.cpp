// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenClose.h"


// Sets default values for this component's properties
UOpenClose::UOpenClose()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenClose::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UOpenClose::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// Poll the Trigger volume
	// TODO IF LMB is pressed then open, if RMB is pressed then close
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}
}

void UOpenClose::OpenDoor()
{
	float yaw = Owner->GetActorRotation().Yaw;

	if (yaw < 1) yaw += 1;
	else yaw = yaw + openAngle/(yaw*5+1);

	if (yaw >= openAngle) return;
	FRotator NewRotation = FRotator(0.f, yaw, 0.f);
	Owner->SetActorRotation(NewRotation);
}

void UOpenClose::CloseDoor()
{
	float yaw = Owner->GetActorRotation().Yaw - 0.5;
	if (yaw <= 0) return;
	FRotator NewRotation = FRotator(0.f, yaw, 0.f);
	Owner->SetActorRotation(NewRotation);
}

