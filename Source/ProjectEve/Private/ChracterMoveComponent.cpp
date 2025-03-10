// Fill out your copyright notice in the Description page of Project Settings.


#include "ChracterMoveComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedPlayerInput.h"

// Sets default values for this component's properties
UChracterMoveComponent::UChracterMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UChracterMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UChracterMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UChracterMoveComponent::SetupInputBinding(class UEnhancedInputComponent* input)
{
	Super::SetupInputBinding(input);

	input->BindAction(IA_L_Stick, ETriggerEvent::Triggered, this, &UChracterMoveComponent::LookUp);
	input->BindAction(IA_R_Stick, ETriggerEvent::Triggered, this, &UChracterMoveComponent::Move);

}

void UChracterMoveComponent::LookUp(const struct FInputActionValue& InputValue)
{
	FVector2D valuse = InputValue.Get<FVector2D>();

	//UE_LOG(LogTemp, Log, TEXT("Look: %f %f"), valuse.X, valuse.Y);
}

void UChracterMoveComponent::Move(const struct FInputActionValue& InputValue)
{
	FVector2D valuse = InputValue.Get<FVector2D>();

	UE_LOG(LogTemp, Log, TEXT("Move: %f %f"), valuse.X, valuse.Y);
}

