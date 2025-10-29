// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/RARobotInterface.h"
#include "Interfaces/RAOutlineInterface.h"
#include "RARobot.generated.h"

UCLASS()
class ROBOTABUSE_API ARARobot : public AActor, public IRARobotInterface, public IRAOutlineInterface
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

	// Called in constructor.
	UFUNCTION()
	void InitializeAndAttachComponents();

	// Sets up the array of meshes we will use for outlining. Used in BeginPlay.
	UFUNCTION()
	void SetupMeshOutlineArray();

// BEGIN INTERFACE FUNCTIONS

	// IRARobotInterface
	bool IsBeingHeld_Implementation() override;
	bool SetIsBeingHeld_Implementation(bool bHeld) override;

	// IRAOutlineInterface
	bool SetOutlineOnOrOff_Implementation(bool bOn, class UPrimitiveComponent* Comp) override;

// END INTERFACE FUNCTIONS



	// Used to check if we are being held/interacted w/ via the torso. Interaction done
	// in RAPlayerController BP.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBeingHeld = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* RobotRootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* UpperBodyComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* LowerBodyComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* HeadComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* LegLComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* LegRComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ArmLComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ArmRComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RobotMeshSceneComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* HeadMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TorsoMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ArmLMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ArmRMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HipsMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LegLMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LegRMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* StatusWidgetComp;


//private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// Which mesh components will we be outlining?
	TArray<class UPrimitiveComponent*> ComponentsToOutline;

	UPROPERTY()
	int32 HighlightInt = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AmtToMoveArm;

private:

	UFUNCTION()
	void ConnectOrDisconnectArmR(bool bConnect);

	UFUNCTION()
	void BindMouseEvents();

	UFUNCTION()
	void OnArmRMouseOver(UPrimitiveComponent* TouchedComp);

	UFUNCTION()
	void OnArmRMouseOverEnd(UPrimitiveComponent* TouchedComp);
};
