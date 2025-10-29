// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RAPCInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URAPCInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ROBOTABUSE_API IRAPCInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class AActor* GetRobotActorRef();
	virtual class AActor* GetRobotActorRef_Implementation() { return nullptr; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetRobotActorRef(AActor* NewRef);
	virtual bool SetRobotActorRef_Implementation(AActor* NewRef) { return false; }

};
