// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimEve.h"
#include "Eve.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ChracterMoveComponent.h"
#include "DataManagerComponent.h"

void UAnimEve::NativeBeginPlay()
{
	Eve = Cast<AEve>(TryGetPawnOwner());
	DataComp = Cast<UDataManagerComponent>(Eve->DataManager);
	MoveComp = Cast<UChracterMoveComponent>(Eve->MoveComp);
}

void UAnimEve::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!Eve) return;
	FVector Velocity = Eve->GetVelocity();
	Speed = Velocity.Size2D();
	WalkAngle = CalculateDirection(Velocity, Eve->GetControlRotation());

	ChangeAngle = MoveComp->getAngleDifference();
	StickAngle = MoveComp->getInputAngle();

	ChangeAngle = 0.0f;

	switch (MoveState)
	{
	case EMoveState::IDLE:
		break;
	case EMoveState::STOP:
		break;
	case EMoveState::WALK: { if (Speed > 800)MoveState = EMoveState::RUN; }
		break;
	case EMoveState::TURN:
		break;
	case EMoveState::RUN:

	default:
		break;
	}
}

void UAnimEve::NativeInitializeAnimation()
{

}

void UAnimEve::PlayMontage(EMontageType type)
{
	Montage_Play(DataComp->CachedMontages[type].MontageAsset);

}

void UAnimEve::getFootPosition()
{
	USkeletalMeshComponent* SkelMesh = Eve->GetMesh();
	FVector LeftFootPos = SkelMesh->GetBoneTransform(SkelMesh->GetBoneIndex("foot_l")).GetLocation();
	FVector RightFootPos = SkelMesh->GetBoneTransform(SkelMesh->GetBoneIndex("foot_r")).GetLocation();
	if (LeftFootPos.X > RightFootPos.X) {
		footPostion = 1.0f;
	}
	else {
		footPostion = 0.0f;

	}
}

void UAnimEve::AnimNotify_TurnEnd()
{
	MoveState = EMoveState::WALK;
	MoveComp->isTurn = false;
	Eve->GetCharacterMovement()->bOrientRotationToMovement = true;
}

