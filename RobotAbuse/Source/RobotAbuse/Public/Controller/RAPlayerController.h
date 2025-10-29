// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTABUSE_API ARAPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 

	// Default contstructor. Put any default values here.
	ARAPlayerController();

	virtual void BeginPlay() override;

	// Called before the RAPlayerController version if BP things need to be set or done.
	UFUNCTION(BlueprintImplementableEvent, Category="Begin Play")
	void BPBeginPlayPre();

	// Called after the C++ version in case something is initialized in BeginPlay in RAPlayerController.
	UFUNCTION(BlueprintImplementableEvent, Category="Begin Play")
	void BPBeginPlayPost();
	
private:

	// Width of the window when building game.
	UPROPERTY(EditDefaultsOnly, Category="Window Resolution")
	int WindowResolutionX;

	// Height of the window when building game.
	UPROPERTY(EditDefaultsOnly, Category="Window Resolution")
	int WindowResolutionY;
};
