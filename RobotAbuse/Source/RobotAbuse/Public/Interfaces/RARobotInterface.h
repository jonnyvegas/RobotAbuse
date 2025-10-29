// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RARobotInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URARobotInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ROBOTABUSE_API IRARobotInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsBeingHeld();
	virtual bool IsBeingHeld_Implementation() { return false; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIsBeingHeld(bool bHeld);
	virtual void SetIsBeingHeld_Implementation(bool bHeld) {  }
};
