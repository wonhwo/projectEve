// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "Eve.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindingDelegate,class UEnhancedInputComponent*)

UCLASS()
class PROJECTEVE_API AEve : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEve();

	FInputBindingDelegate InputBindingDelegate;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	class UCharacterBaseComponent* BaseComp;

	UPROPERTY(EditAnywhere)
	class UActionComponent* ActionComp;

	UPROPERTY(EditAnywhere)
	class UChracterMoveComponent* MoveComp;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();

	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputMappingContext* IMC_Eve;






};
