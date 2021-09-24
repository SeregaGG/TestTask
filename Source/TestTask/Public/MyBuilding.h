// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MyBuilding.generated.h"

UCLASS()
class TESTTASK_API AMyBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBuilding();

	UPROPERTY()
	USceneComponent* Root;

	class UMaterialInstanceDynamic* MyMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	FVector GlobalTargetLocation;

	UFUNCTION(BlueprintCallable)
	void MyOnReleased(class UPrimitiveComponent* OtherComp, FKey ReleasedKey);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
