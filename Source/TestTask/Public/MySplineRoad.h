// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "MySplineRoad.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API UMySplineRoad : public USplineComponent
{
	GENERATED_BODY()

public:
	UMySplineRoad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(CallInEditor)
		void AddCrossroad();
};
