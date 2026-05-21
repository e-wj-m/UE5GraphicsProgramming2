// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MainMenuGameMode.h"
#include "GUI/MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		UMainMenuWidget* MenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		MenuWidget->AddToViewport();
		
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->SetInputMode(FInputModeUIOnly());
		}
		
	}
}

