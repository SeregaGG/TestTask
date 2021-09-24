// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWithSpline.h"

// Sets default values
AActorWithSpline::AActorWithSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CarSplineRoad = CreateDefaultSubobject<USplineComponent>(TEXT("CarSplineRoad"));
	RootComponent = CarSplineRoad;
}

// Called when the game starts or when spawned
void AActorWithSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorWithSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

