// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/RAPlayerController.h"
#include "GameFramework/GameUserSettings.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Interfaces/RARobotInterface.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

ARAPlayerController::ARAPlayerController()
{
	WindowResolutionX = 1280;
	WindowResolutionY = 720;
}

void ARAPlayerController::BeginPlay()
{
	BPBeginPlayPre();
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	
	// Double check we don't crash due to null ref.
	if (GameSettings)
	{
		// Set the settings and apply them (forgetting to apply results in no settings changed).
		GameSettings->SetFullscreenMode(EWindowMode::Windowed);
		GameSettings->SetScreenResolution(FIntPoint(WindowResolutionX, WindowResolutionY));
		GameSettings->ApplyResolutionSettings(false);
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Settings was invalid! RAPC BeginPlay"));
	}

	BPBeginPlayPost();
}

void ARAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	InputSystem->ClearAllMappings();
	InputSystem->AddMappingContext(InputMC, 0);
	PC->InputComponent->BindAction("LeftMouseButton", IE_Released, this, &ARAPlayerController::LMBReleased);
	PC->InputComponent->BindAction("QuitGame", IE_Pressed, this, &ARAPlayerController::QuitGame);
}

void ARAPlayerController::LMBReleased()
{
	if (this->Implements<URAPCInterface>())
	{
		if (IRAPCInterface::Execute_GetRobotActorRef(this) && IRAPCInterface::Execute_GetRobotActorRef(this)->Implements<URARobotInterface>())
		{
			if (IRARobotInterface::Execute_IsBeingHeld(IRAPCInterface::Execute_GetRobotActorRef(this)))
			{
				IRARobotInterface::Execute_SetIsBeingHeld(IRAPCInterface::Execute_GetRobotActorRef(this), false);
			}
		}
		IRAPCInterface::Execute_SetRobotActorRef(this, nullptr);
	}
	SetIgnoreLookInput(false);
}

void ARAPlayerController::QuitGame()
{
	TEnumAsByte<EQuitPreference::Type> QuitPref = EQuitPreference::Quit;
	UKismetSystemLibrary::QuitGame(this, this, QuitPref, false);
}

class AActor* ARAPlayerController::GetRobotActorRef_Implementation()
{
	return RobotActorRef;
}

bool ARAPlayerController::SetRobotActorRef_Implementation(AActor* NewRef)
{
	RobotActorRef = NewRef;
	return false;
}