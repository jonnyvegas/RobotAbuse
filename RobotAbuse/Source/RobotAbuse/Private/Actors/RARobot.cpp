// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RARobot.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Interfaces/RAPCInterface.h"
#include "Interfaces/RAWidgetStatusInterface.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "../../../../../../../Source/Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values
ARARobot::ARARobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitializeAndAttachComponents();
	SetupMeshOutlineArray();
	
	HighlightInt = 2;

	BindMouseEvents();
	bArmRConnected = true;
	InterpSpeed = 10.f;
}

// Called when the game starts or when spawned
void ARARobot::BeginPlay()
{
	Super::BeginPlay();
	BindMouseEvents();
	ControllerRef = UGameplayStatics::GetPlayerController(this, 0);
}

// Called every frame
void ARARobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsBeingHeld && ControllerRef)
	{
		ControllerRef->GetMousePosition(MouseLocX, MouseLocY);
		MousePos = FVector2D(MouseLocX, MouseLocY);
		// Mouse to world so we can get a ray from the mouse into the world and hold the Robot there.
		UGameplayStatics::DeprojectScreenToWorld(ControllerRef, MousePos, WorldPos, WorldDir);
		TargetPos = (WorldPos + (WorldDir * TraceDistance));
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetPos, DeltaTime, InterpSpeed), true);
	}
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
	// In case this gets called multiple times, only want one copy.
	ComponentsToOutline.Empty();
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
	Comp->SetRenderCustomDepth(bOn);
	if (bOn)
	{
		Comp->SetCustomDepthStencilValue(HighlightInt);
	}
	else
	{
		Comp->SetCustomDepthStencilValue(0);
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

	UUserWidget* WidgetObj = StatusWidgetComp->GetUserWidgetObject();
	if (WidgetObj->Implements<URAWidgetStatusInterface>())
	{
		IRAWidgetStatusInterface::Execute_SetAttachedOrDetached(WidgetObj, bConnect);
	}
}

void ARARobot::BindMouseEvents()
{
	ArmRMeshComp->OnBeginCursorOver.AddDynamic(this, &ARARobot::OnArmRMouseOver);
	ArmRMeshComp->OnEndCursorOver.AddDynamic(this, &ARARobot::OnArmRMouseOverEnd);

	ArmRMeshComp->OnClicked.AddDynamic(this, &ARARobot::OnArmRClicked);

	TorsoMeshComp->OnBeginCursorOver.AddDynamic(this, &ARARobot::OnTorsoMouseOver);
	TorsoMeshComp->OnEndCursorOver.AddDynamic(this, &ARARobot::OnTorsoMouseOverEnd);

	TorsoMeshComp->OnClicked.AddDynamic(this, &ARARobot::OnTorsoClicked);
}

void ARARobot::OnArmRMouseOver(UPrimitiveComponent* TouchedComp)
{
	if (this->Implements<URAOutlineInterface>())
	{
		IRAOutlineInterface::Execute_SetOutlineOnOrOff(this, true, ArmRMeshComp);
	}
}

void ARARobot::OnArmRMouseOverEnd(UPrimitiveComponent* TouchedComp)
{
	if (this->Implements<URAOutlineInterface>())
	{
		IRAOutlineInterface::Execute_SetOutlineOnOrOff(this, false, ArmRMeshComp);
	}
}

void ARARobot::OnArmRClicked(UPrimitiveComponent* Comp, const FKey ButtonPressed)
{
	bArmRConnected = !bArmRConnected;
	ConnectOrDisconnectArmR(bArmRConnected);
}

void ARARobot::OnTorsoMouseOver(UPrimitiveComponent* TouchedComp)
{
	if (this->Implements<URAOutlineInterface>())
	{
		for (UPrimitiveComponent* Comp : ComponentsToOutline)
		{
			IRAOutlineInterface::Execute_SetOutlineOnOrOff(this, true, Comp);
		}
		
	}
	APlayerController* PCRef = UGameplayStatics::GetPlayerController(this, 0);
	if (PCRef && PCRef->Implements<URAPCInterface>())
	{
		IRAPCInterface::Execute_SetRobotActorRef(PCRef, this);
	}
}

void ARARobot::OnTorsoMouseOverEnd(UPrimitiveComponent* TouchedComp)
{
	if (this->Implements<URAOutlineInterface>())
	{
		for (UPrimitiveComponent* Comp : ComponentsToOutline)
		{
			IRAOutlineInterface::Execute_SetOutlineOnOrOff(this, false, Comp);
		}

	}
}

void ARARobot::OnTorsoClicked(UPrimitiveComponent* Comp, const FKey ButtonPressed)
{
	
	ControllerRef = UGameplayStatics::GetPlayerController(this, 0);
	if (ControllerRef)
	{
		TraceDistance = GetDistanceTo(ControllerRef->GetPawn());
		ControllerRef->SetIgnoreLookInput(true);
	}
	bIsBeingHeld = true;
}
