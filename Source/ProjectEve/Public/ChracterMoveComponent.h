// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterBaseComponent.h"
#include "ChracterMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTEVE_API UChracterMoveComponent : public UCharacterBaseComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UChracterMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	//class UInputComponent*

public:
	//인풋 바인딩 함수
	void SetupInputBinding(class UEnhancedInputComponent* input) override;

	//카메라 시선 입력 함수
	void LookUp(const struct FInputActionValue& InputValue);

	//캐릭터 무브 입력 함수
	void Move(const struct FInputActionValue& InputValue);

public:
	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* IA_L_Stick;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* IA_R_Stick;

};
