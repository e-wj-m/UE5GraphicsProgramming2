// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GRAPHICSPROGRAMMING2_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;

	UFUNCTION()
	void OnStartGameClicked();

	UFUNCTION()
	void OnExitGameClicked();
};
