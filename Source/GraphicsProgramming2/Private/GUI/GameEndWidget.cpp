// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/GameEndWidget.h"
#include "Kismet/GameplayStatics.h"

void UGameEndWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameEndWidget::OnMainMenuClicked);
	}
}

void UGameEndWidget::SetResultMessage(const FText& Message)
{
	if (ResultText)
	{
		ResultText->SetText(Message);
	}
}

void UGameEndWidget::OnMainMenuClicked()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenuLevel"));
}
