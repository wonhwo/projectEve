// Fill out your copyright notice in the Description page of Project Settings.


#include "ChracterMoveComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedPlayerInput.h"
#include "Eve.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	Eve->GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	// ...

}


// Called every frame
void UChracterMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	{
		//�÷��̾ �ٶ󺸴� �������� �̵��ϰ� ī�޶� ȸ���� ������ ���� �ʵ��� ������
		FVector WorldDirection = FTransform(Eve->GetControlRotation()).TransformVector(Direction);
		WorldDirection.Z = 0;
		WorldDirection.Normalize();
		Eve->AddMovementInput(WorldDirection,Direction.Size());

		Direction = FVector::ZeroVector;
	}
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


	FRotator ControlRotation = Eve->GetControlRotation();
	float NewPitch = ControlRotation.Pitch + valuse.Y;

	NewPitch = FMath::Clamp(NewPitch, -35.0f, 35.0f);

	Eve->GetController()->SetControlRotation(FRotator(NewPitch, ControlRotation.Yaw+valuse.X, ControlRotation.Roll));

}

void UChracterMoveComponent::Move(const struct FInputActionValue& InputValue)
{
	FVector2D valuse = InputValue.Get<FVector2D>();
	//������� ���ϱ�
	Direction.X = valuse.Y;
	Direction.Y = valuse.X;

	FTimerHandle RunCheckTimer;
	//��ƽ ���⿡ ���� �ӵ� �ִ�ġ�� ���޽� �ִ�ġ ���� 2���� ������ �޸��� �ߵ�
	if (Velocity == Eve->GetMovementComponent()->GetMaxSpeed()) {
		currentTime += GetWorld()->DeltaTimeSeconds;
		if (currentTime >= 2)RunCheck();
	}
	//��ƽ ���Ⱑ �����̶� �������� ������ �޸��� ����
	if(Direction.Size()<=1.0f){
		currentTime = 0.0f;
		Eve->GetCharacterMovement()->MaxWalkSpeed = 800;
	}



}
//������ �޸��� �ߵ� �Լ�
void UChracterMoveComponent::RunCheck()
{
	UE_LOG(LogTemp, Log, TEXT("run!"));
	Eve->GetCharacterMovement()->MaxWalkSpeed = 1600;
}

