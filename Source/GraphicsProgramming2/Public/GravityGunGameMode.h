// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GravityGunGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GRAPHICSPROGRAMMING2_API AGravityGunGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;
};
