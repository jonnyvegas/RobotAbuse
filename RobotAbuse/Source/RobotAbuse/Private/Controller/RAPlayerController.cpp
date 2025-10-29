// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/RAPlayerController.h"
#include "GameFramework/GameUserSettings.h"

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
		
		//UEnhancedInputLocalPlayerSubsystem::AddMappingContext()
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Settings was invalid! RAPC BeginPlay"));
	}

	BPBeginPlayPost();
}

class AActor* ARAPlayerController::GetRobotActorRef_Implementation()
{
	return RobotActorRef;
}

void ARAPlayerController::SetRobotActorRef_Implementation(AActor* NewRef)
{
	RobotActorRef = NewRef;
}