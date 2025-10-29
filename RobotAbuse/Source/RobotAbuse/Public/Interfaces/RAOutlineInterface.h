// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RAOutlineInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URAOutlineInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ROBOTABUSE_API IRAOutlineInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Turns the outline on or off based on bOn.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetOutlineOnOrOff(bool bOn, class UPrimitiveComponent* Comp);
	virtual bool SetOutlineOnOrOff_Implementation(bool bOn, UPrimitiveComponent* Comp) { return false; }
};
