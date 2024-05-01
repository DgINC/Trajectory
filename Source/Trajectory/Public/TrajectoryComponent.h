// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PoseSearch/PoseSearchTrajectoryLibrary.h"
#include "TrajectoryComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTrajectoryComponent, Log, All);

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent), Experimental)
class TRAJECTORY_API UTrajectoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrajectoryComponent(const FObjectInitializer& ObjectInitializer);

	// Begin UActorComponent Interface
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void BeginPlay() override;
	// End UActorComponent Interface

protected:
	UFUNCTION()
	void OnMovementUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity);

	// Trajectory stored in world space so it can be directly passed to Motion Matching.
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Trajectory")
	FPoseSearchQueryTrajectory IOTrajectory;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Trajectory")
	FPoseSearchQueryTrajectory OTrajectory;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Trajectory Settings")
	FPoseSearchTrajectoryData TrajectoryData;

	TObjectPtr<class ACharacter> Character;
	TObjectPtr<class UAnimInstance> AnimInstance;
	struct FPoseSearchTrajectory_WorldCollisionResults CollisionResult;
	TArray<AActor*> ActorsToIgnore;

	float DesiredControllerYawLastUpdate = 0.f;
};
