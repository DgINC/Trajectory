// Fill out your copyright notice in the Description page of Project Settings.


#include "TrajectoryComponent.h"
#include "GameFramework/Character.h"
#include "HAL/IConsoleManager.h"

DEFINE_LOG_CATEGORY(LogTrajectoryComponent);

UTrajectoryComponent::UTrajectoryComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	bWantsInitializeComponent = true;

}

void UTrajectoryComponent::InitializeComponent()
{
	Super::InitializeComponent();
	Character = Cast<ACharacter>(GetOwner());

	if (ensure(Character != nullptr))
	{
		Character->OnCharacterMovementUpdated.AddDynamic(this, &UTrajectoryComponent::OnMovementUpdated);
	}
	else
	{
		UE_LOG(LogTrajectoryComponent, Error, TEXT("UCharacterTrajectoryComponent requires its owner to be ACharacter"));
	}
}

void UTrajectoryComponent::UninitializeComponent()
{
	if (ensure(Character != nullptr))
	{
		Character->OnCharacterMovementUpdated.RemoveDynamic(this, &UTrajectoryComponent::OnMovementUpdated);
	}
	else
	{
		UE_LOG(LogTrajectoryComponent, Error, TEXT("UCharacterTrajectoryComponent requires its owner to be ACharacter"));
	}
	Super::UninitializeComponent();
}

void UTrajectoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(Character != nullptr))
	{
		AnimInstance = Character->GetMesh()->GetAnimInstance();
	}
	else
	{
		UE_LOG(LogTrajectoryComponent, Error, TEXT("UCharacterTrajectoryComponent requires its owner to be ACharacter"));
	}
}

void UTrajectoryComponent::OnMovementUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity)
{
	UPoseSearchTrajectoryLibrary::PoseSearchGenerateTrajectory(AnimInstance, TrajectoryData, DeltaSeconds, IOTrajectory, DesiredControllerYawLastUpdate, OTrajectory);
	UPoseSearchTrajectoryLibrary::HandleTrajectoryWorldCollisions(Character->GetWorld(), AnimInstance, IOTrajectory, true, 10.f, OTrajectory, CollisionResult, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::None);
}
