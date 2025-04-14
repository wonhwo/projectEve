// Fill out your copyright notice in the Description page of Project Settings.


#include "DataManagerComponent.h"
#include "FMontageEntry.h"
#include "MontageDataAsset.h"
#include "AnimEve.h"

// Sets default values for this component's properties
UDataManagerComponent::UDataManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	{
		static ConstructorHelpers::FObjectFinder<UMontageDataAsset> MontageDataFinder(TEXT("/Script/ProjectEve.MontageDataAsset'/Game/Data/DA_Montage.DA_Montage'"));
		if (MontageDataFinder.Succeeded())
		{
			MontageData = MontageDataFinder.Object;
		}
	}

}

// Called when the game starts
void UDataManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	CachedMontages = MontageData->MontageDataAsset;
}


// Called every frame
void UDataManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

