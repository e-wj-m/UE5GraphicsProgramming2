// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityGunGameMode.h"

void AGravityGunGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. Its color is red.
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello, world! This is GravityGunGameMode! A game that will be developed for both Graphics Programming 2 and Project 2 of Physics for Game Programmers!"));
}
