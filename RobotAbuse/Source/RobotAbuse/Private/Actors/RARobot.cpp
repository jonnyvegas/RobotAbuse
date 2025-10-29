// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RARobot.h"

// Sets default values
ARARobot::ARARobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARARobot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARARobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ARARobot::IsBeingHeld_Implementation()
{
	return bIsBeingHeld;
}

void ARARobot::SetIsBeingHeld_Implementation(bool bHeld)
{
	bIsBeingHeld = bHeld;
}

