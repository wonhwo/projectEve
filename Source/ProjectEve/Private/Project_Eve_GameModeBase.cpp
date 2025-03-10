// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_Eve_GameModeBase.h"
#include "Project_Eve_PlayerController.h"

AProject_Eve_GameModeBase::AProject_Eve_GameModeBase()
{
	PlayerControllerClass = AProject_Eve_PlayerController::StaticClass();

	ConstructorHelpers::FClassFinder<APawn> pawn(L"/Script/Engine.Blueprint'/Game/Blueprint/BP_Eve.BP_Eve_C'");
	if (pawn.Succeeded())
		DefaultPawnClass = pawn.Class;

}
