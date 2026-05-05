// Fill out your copyright notice in the Description page of Project Settings.


#include "Slate/SFPSSettingsWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SFPSSettingsWidget::Construct(const FArguments& InArgs)
{
	FPSGameHUD = InArgs._FPSGameHUD;
	MyInt = InArgs._MyInt;

	const FMargin ContentPadding(800.0f, 300.0f);

	// Title Settings
	const FText TitleText = FText::FromString(TEXT("Settings Menu"));
	FSlateFontInfo TitleFontInfo = FCoreStyle::Get().GetFontStyle("Embossed Text");
	TitleFontInfo.Size = 60;

	// Button Settings 
	const FMargin ButtonPadding(10.0f);
	FSlateFontInfo ButtonFontInfo = FCoreStyle::Get().GetFontStyle("Embossed Text");
	ButtonFontInfo.Size = 40;


	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FLinearColor::Black)
		]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
			[
				SNew(SVerticalBox)
				// Title Text
				+SVerticalBox::Slot()
					[
						SNew(STextBlock)
						.Text(TitleText)
						.Font(TitleFontInfo)
						.Justification(ETextJustify::Center)
					]
					// Resume Button
					+SVerticalBox::Slot()
					.Padding(ButtonPadding)
					[
						SNew(SButton)
						.OnClicked(this, &SFPSSettingsWidget::OnResumeClicked)
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("Resume")))
							.Font(ButtonFontInfo)
							.Justification(ETextJustify::Center)
						]
					]

					// Int Button
					+SVerticalBox::Slot()
					.Padding(ButtonPadding)
					[
						SNew(SButton)
						.OnClicked(this, &SFPSSettingsWidget::OnIntClicked)
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("Int")))
							.Font(ButtonFontInfo)
							.Justification(ETextJustify::Center)
						]
					]

				    // Quit Button
				    +SVerticalBox::Slot()
					.Padding(ButtonPadding)
					[
						SNew(SButton)
						.OnClicked(this, &SFPSSettingsWidget::OnQuitClicked)
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("Quit")))
							.Font(ButtonFontInfo)
							.Justification(ETextJustify::Center)
						]
					]
			]
	];

}
FReply SFPSSettingsWidget::OnResumeClicked() const
{
	if (FPSGameHUD.IsValid())
	{
		FPSGameHUD->HideSettingsWidget();
	}

	return FReply::Handled();
}

FReply SFPSSettingsWidget::OnIntClicked() const
{
	UE_LOG(LogTemp, Warning, TEXT("MyInt: %d"), MyInt);
	return FReply::Handled();
}

FReply SFPSSettingsWidget::OnQuitClicked() const
{
	if (FPSGameHUD.IsValid())
	{
		FPSGameHUD->PlayerOwner->ConsoleCommand(TEXT("Quitting the non existent game... Damn you're good at quitting!"));
	}

	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
