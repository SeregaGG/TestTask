// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TrafficLights.generated.h"

UCLASS()
class TESTTASK_API ATrafficLights : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrafficLights();
	UPROPERTY()
		USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* FirstRoadStart;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* FirstRoadEnd;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* SecondRoadStart;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* SecondRoadEnd;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* LightFirstStart;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* LightFirstEnd;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* LightSecondStart;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* LightSecondEnd;

	UPROPERTY(EditAnywhere)
	class UMaterial* OnMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterial* OffMaterial;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
		bool RedLight = false;

	UPROPERTY(BlueprintReadWrite);
	bool bCanDriveFirst = false;
	
	UPROPERTY(BlueprintReadWrite);
	bool bCanDriveSecond = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
		float CrossroadRadius = 500;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
		float HeightLights = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
		float BoxSizeX = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
		float BoxSizeY = 300;

	void SwitchLight();

	UFUNCTION()
		void OnFirstOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnFirstOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnSecondOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnSecondOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
