// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithSpline.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CarSpline.generated.h"

UCLASS()
class TESTTASK_API ACarSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarSpline();
	UPROPERTY()
		USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* CarMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeginPlayMesh")
		class UStaticMesh* BeginPlayCarMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActorWithSpline> ActorWithSplineClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActorWithSpline* SplineActorRoad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* TriggerBox;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	UFUNCTION(CallInEditor)
		void SpawnSpline();

	UFUNCTION()
		void dsa();

	UFUNCTION()
		void CarRiding();

	UFUNCTION()
		void DoCarAcceleration();

	UFUNCTION()
		void DoCarStop();

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxSpeed = 110;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StopSpeedDelta = 30;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Acceleration = 30;
	
	UPROPERTY(BlueprintReadWrite)
		float CurrentSpeed = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDrawDebug = false;
	
	float CurrentDistance = 0.f;

	bool bStopLight = false;
	int bOnCrossroad = 0;
	bool bTestOnCrossroad = false;
	
};
