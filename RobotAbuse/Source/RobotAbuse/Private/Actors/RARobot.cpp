// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RARobot.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ARARobot::ARARobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitializeAndAttachComponents();
	SetupMeshOutlineArray();
	
	HighlightInt = 2;
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

void ARARobot::InitializeAndAttachComponents()
{
	RobotRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RobotRootComp"));
	SetRootComponent(RobotRootComp);

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetupAttachment(RobotRootComp);

	// Connect roots and widget to capsule.

	RobotMeshSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RobotMeshSceneComp"));
	RobotMeshSceneComp->SetupAttachment(CapsuleComp);

	UpperBodyComp = CreateDefaultSubobject<USceneComponent>(TEXT("UpperBodyComp"));
	UpperBodyComp->SetupAttachment(RobotMeshSceneComp);

	LowerBodyComp = CreateDefaultSubobject<USceneComponent>(TEXT("LowerBodyComp"));
	LowerBodyComp->SetupAttachment(RobotMeshSceneComp);

	HeadComp = CreateDefaultSubobject<USceneComponent>(TEXT("HeadComp"));
	HeadComp->SetupAttachment(RobotMeshSceneComp);

	//Connect meshes to body roots.
	TorsoMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoMeshComp"));
	TorsoMeshComp->SetupAttachment(UpperBodyComp);

	ArmRComp = CreateDefaultSubobject<USceneComponent>(TEXT("ArmRComp"));
	ArmRComp->SetupAttachment(TorsoMeshComp);

	ArmRMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmRMeshComp"));
	ArmRMeshComp->SetupAttachment(ArmRComp);

	ArmLComp = CreateDefaultSubobject<USceneComponent>(TEXT("ArmLComp"));
	ArmLComp->SetupAttachment(TorsoMeshComp);

	ArmLMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmLMeshComp"));
	ArmLMeshComp->SetupAttachment(ArmLComp);

	HipsMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HipsMeshComp"));
	HipsMeshComp->SetupAttachment(LowerBodyComp);

	LegLComp = CreateDefaultSubobject<USceneComponent>(TEXT("LegLComp"));
	LegLComp->SetupAttachment(LowerBodyComp);

	LegLMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LegLMeshComp"));
	LegLMeshComp->SetupAttachment(LegLComp);

	LegRComp = CreateDefaultSubobject<USceneComponent>(TEXT("LegRComp"));
	LegRComp->SetupAttachment(LowerBodyComp);

	LegRMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LegRMeshComp"));
	LegRMeshComp->SetupAttachment(LegRComp);

	HeadMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadMeshComp"));
	HeadMeshComp->SetupAttachment(HeadComp);

	StatusWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusWidgetComp"));
	StatusWidgetComp->SetupAttachment(RootComponent);
}

void ARARobot::SetupMeshOutlineArray()
{
	ComponentsToOutline.Add(HeadMeshComp);
	ComponentsToOutline.Add(LegRMeshComp);
	ComponentsToOutline.Add(LegLMeshComp);
	ComponentsToOutline.Add(ArmLMeshComp);
	ComponentsToOutline.Add(ArmRMeshComp);
	ComponentsToOutline.Add(HipsMeshComp);
	ComponentsToOutline.Add(TorsoMeshComp);
}


bool ARARobot::SetOutlineOnOrOff_Implementation(bool bOn, class UPrimitiveComponent* Comp)
{
	for (UPrimitiveComponent* MeshComp : ComponentsToOutline)
	{
		MeshComp->SetRenderCustomDepth(bOn);
		if (bOn)
		{
			MeshComp->SetCustomDepthStencilValue(HighlightInt);
		}
		else
		{
			MeshComp->SetCustomDepthStencilValue(0);
		}
	}
	return false;
}

bool ARARobot::IsBeingHeld_Implementation()
{
	return bIsBeingHeld;
}

bool ARARobot::SetIsBeingHeld_Implementation(bool bHeld)
{
	bIsBeingHeld = bHeld;
	return bIsBeingHeld;
}


void ARARobot::ConnectOrDisconnectArmR(bool bConnect)
{
	if (bConnect)
	{
		ArmRMeshComp->SetRelativeLocation(FVector(FVector::ZeroVector));
	}
	else
	{
		ArmRMeshComp->SetRelativeLocation(FVector(AmtToMoveArm * -1.f, 0.f, 0.f));
	}
}
