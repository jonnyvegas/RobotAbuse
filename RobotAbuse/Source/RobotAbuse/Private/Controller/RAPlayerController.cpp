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
		GameSettings->SetFullscreenMode(EWindowMode::Windowed);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Settings was invalid! RAPC BeginPlay"));
	}

	BPBeginPlayPost();
}
