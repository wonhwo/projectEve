// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBaseComponent.h"
#include "Eve.h"

// Sets default values for this component's properties
UCharacterBaseComponent::UCharacterBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	// ...
}
void UCharacterBaseComponent::SetupInputBinding(class UEnhancedInputComponent* input)
{

}


void UCharacterBaseComponent::InitializeComponent()
{

	Super::InitializeComponent();
	Eve = Cast<AEve>(GetOwner());
	Eve->InputBindingDelegate.AddUObject(this, &UCharacterBaseComponent::SetupInputBinding);
}

// Called when the game starts
void UCharacterBaseComponent::BeginPlay()
{
	Super::BeginPlay();
	Eve = Cast<AEve>(GetOwner());

	// ...

}


// Called every frame
void UCharacterBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



