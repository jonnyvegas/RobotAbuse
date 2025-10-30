// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/RAPCInterface.h"
#include "RAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTABUSE_API ARAPlayerController : public APlayerController, public IRAPCInterface
{
	GENERATED_BODY()

public: 

	// Default constructor. Put any default values here.
	ARAPlayerController();

	// Override for default BeginPlay.
	virtual void BeginPlay() override;

	// Called before the RAPlayerController version if BP things need to be set or done.
	UFUNCTION(BlueprintImplementableEvent, Category="Begin Play")
	void BPBeginPlayPre();

	// Called after the C++ version in case something is initialized in BeginPlay in RAPlayerController.
	UFUNCTION(BlueprintImplementableEvent, Category="Begin Play")
	void BPBeginPlayPost();

//INTERFACE FUNCTIONS

	class AActor* GetRobotActorRef_Implementation() override;
	bool SetRobotActorRef_Implementation(AActor* NewRef) override;
	
private:

	// Reference to the RobotActor to use to call interfaces.
	UPROPERTY()
	AActor* RobotActorRef;

	// Width of the window when building game.
	UPROPERTY(EditDefaultsOnly, Category="Window Resolution")
	int WindowResolutionX;

	// Height of the window when building game.
	UPROPERTY(EditDefaultsOnly, Category="Window Resolution")
	int WindowResolutionY;

	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* InputMC;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction* MouseClickAction;

};
