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

	virtual void SetupInputComponent() override;

//INTERFACE FUNCTIONS

	class AActor* GetRobotActorRef_Implementation() override;
	bool SetRobotActorRef_Implementation(AActor* NewRef) override;
	
private:

	UFUNCTION()
	void LMBReleased();

	UFUNCTION()
	void QuitGame();

	// Reference to the RobotActor to use to call interfaces.
	UPROPERTY()
	AActor* RobotActorRef;

	// Width of the window when building game.
	UPROPERTY(EditDefaultsOnly, Category="Window Resolution")
	int WindowResolutionX;

	// Height of the window when building game.
	UPROPERTY(EditDefaultsOnly, Category="Window Resolution")
	int WindowResolutionY;

	// Used for new input system.
	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* InputMC;

	// New input system WIP.
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* MouseClickAction;

};
