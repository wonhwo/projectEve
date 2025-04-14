// Fill out your copyright notice in the Description page of Project Settings.


#include "ChracterMoveComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedPlayerInput.h"
#include "Eve.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AnimEve.h"

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

	Eve->bUseControllerRotationYaw = false;
	Eve->GetCharacterMovement()->bOrientRotationToMovement = true;

	// ...

}


// Called every frame
void UChracterMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	{
		//플레이어가 바라보는 방향으로 이동하고 카메라 회전에 영향을 받지 않도록 설정함
		FVector WorldDirection = FTransform(Eve->GetControlRotation()).TransformVector(Direction);
		WorldDirection.Z = 0;
		WorldDirection.Normalize();
		    Eve->AddMovementInput(WorldDirection,Direction.Size());

		Direction = FVector::ZeroVector;

	}
    //가속도 계산
    {
        FVector CurrentVelocity = Eve->GetCharacterMovement()->Velocity;

        PreviousVelocity = CurrentVelocity;
        PreviousSpeed = CurrentVelocity.Size();

        if (DeltaTime > 0.f)
        {
            Acceleration = (CurrentVelocity.Size() - PreviousSpeed) / DeltaTime;
        }
        else
        {
            Acceleration = 0.f;
        }
    }

}
void UChracterMoveComponent::SetupInputBinding(class UEnhancedInputComponent* input)
{
	Super::SetupInputBinding(input);

	input->BindAction(IA_R_Stick, ETriggerEvent::Triggered, this, &UChracterMoveComponent::LookUp);

	input->BindAction(IA_L_Stick, ETriggerEvent::Triggered, this, &UChracterMoveComponent::Move);

	input->BindAction(IA_Jump, ETriggerEvent::Started, this, &UChracterMoveComponent::Jump);

	input->BindAction(IA_L_Stick, ETriggerEvent::Started, this, &UChracterMoveComponent::OnMoveStarted);
	input->BindAction(IA_L_Stick, ETriggerEvent::Completed, this, &UChracterMoveComponent::Movestop);
	input->BindAction(IA_L_StickClick, ETriggerEvent::Started, this, &UChracterMoveComponent::StartSprint);

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
    FVector2D values = InputValue.Get<FVector2D>();
    Direction.X = values.Y;
    Direction.Y = values.X;
    if(Anim->MoveState==EMoveState::RUN){
    if (FMath::Abs(AngleDifference)>= 150) {
        if (isTurn) return;
        isTurn = true;

		Anim->MoveState = EMoveState::TURN;
        Eve->GetCharacterMovement()->GroundFriction = 0;
            FTimerHandle handler;
        auto changeState = [this]() {
            if (Anim->MoveState == EMoveState::WALK|| Anim->MoveState == EMoveState::RUN) return;
            Eve->GetCharacterMovement()->GroundFriction = 8;
            Anim->MoveState = EMoveState::WALK;
            isTurn = false;
            Eve->GetCharacterMovement()->MaxWalkSpeed = 1200;

            };
        GetWorld()->GetTimerManager().SetTimer(handler, changeState, 0.6f, false);
    }
    }

    if (Direction.SizeSquared() > 0.2f)
    {
        FVector CharacterForward = Eve->GetActorForwardVector();
        CurrentCharacterAngle = FMath::Atan2(CharacterForward.Y, CharacterForward.X);
        CurrentCharacterAngle = FMath::RadiansToDegrees(CurrentCharacterAngle);

        FRotator ControlRotation = Eve->GetController()->GetControlRotation();
        FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
        FVector InputWorldDirection = FRotationMatrix(YawRotation).TransformVector(FVector(Direction.X, Direction.Y, 0.f));

        InputAngle = FMath::Atan2(InputWorldDirection.Y, InputWorldDirection.X);
        InputAngle = FMath::RadiansToDegrees(InputAngle);

        // 두 방향 간의 각도 차이
        AngleDifference = FMath::FindDeltaAngleDegrees(CurrentCharacterAngle, InputAngle);
    }

    StickMagnitude = Direction.Size(); // 0~1

    FTimerHandle RunCheckTimer;
    if (Velocity == Eve->GetMovementComponent()->GetMaxSpeed())
    {
        currentTime += GetWorld()->DeltaTimeSeconds;
        isRun = false;

        if (currentTime >= 5 && Velocity == 800.0f)
        {
            RunCheck();
        }
    }

    if (StickMagnitude <= 0.3f)
    {
        isRun = true;
        currentTime = 0.0f;
        Eve->GetCharacterMovement()->MaxWalkSpeed = 600;
    }
}
//하이퍼 달리기 발동 함수
void UChracterMoveComponent::RunCheck()
{
	if (isRun)return;
	Eve->GetCharacterMovement()->MaxWalkSpeed = 1200;

}

void UChracterMoveComponent::Jump()
{
	Eve->Jump();
}

void UChracterMoveComponent::OnMoveStarted(const FInputActionValue& Value)
{
	    Anim->MoveState = EMoveState::WALK;
}

void UChracterMoveComponent::Movestop()
{
    if (Anim->MoveState == EMoveState::WALK|| Anim->MoveState == EMoveState::RUN) {
        if (isTurn)return;
        Anim->getFootPosition();
        Anim->MoveState = EMoveState::STOP;
        Anim->PreviousSpeed = Anim->Speed;

    }

    FTimerHandle handler;
    auto changeState = [this]() {
        if (Anim->MoveState == EMoveState::WALK) return;
        Anim->MoveState = EMoveState::IDLE;
        };
    GetWorld()->GetTimerManager().SetTimer(handler, changeState, 1.0f,false);
}

void UChracterMoveComponent::StartSprint()
{
	Eve->GetCharacterMovement()->MaxWalkSpeed = 800;
	currentTime = 0.0f;

}

