// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameEndWidget.generated.h"

/**
 * 
 */
UCLASS()
class GRAPHICSPROGRAMMING2_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResultText;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UFUNCTION()
	void SetResultMessage(const FText& Message);

	UFUNCTION()
	void OnMainMenuClicked();

};
