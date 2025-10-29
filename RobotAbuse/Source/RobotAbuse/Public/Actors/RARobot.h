// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/RARobotInterface.h"
#include "RARobot.generated.h"

UCLASS()
class ROBOTABUSE_API ARARobot : public AActor, public IRARobotInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARARobot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBeingHeld = false;

// INTERFACE FUNCTIONS

	bool IsBeingHeld_Implementation() override;
	void SetIsBeingHeld_Implementation(bool bHeld) override;
};
