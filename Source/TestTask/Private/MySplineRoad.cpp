// Fill out your copyright notice in the Description page of Project Settings.


#include "MySplineRoad.h"

UMySplineRoad::UMySplineRoad()
{
	bDrawDebug = true;
}

void UMySplineRoad::BeginPlay()
{
	Super::BeginPlay();
}

void UMySplineRoad::AddCrossroad()
{
	FVector SpawnLocation = GetLocationAtSplinePoint(GetNumberOfSplinePoints()-1, ESplineCoordinateSpace::World);
	GetWorld()->SpawnActor<UMySplineRoad>(UMySplineRoad::StaticClass(), SpawnLocation, GetComponentRotation());
}
