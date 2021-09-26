// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBuilding.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "MyFreeCam.generated.h"

UCLASS()
class TESTTASK_API AMyFreeCam : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyFreeCam();

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UFloatingPawnMovement* MyMovementComponentComp;
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Root;*/
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FRotator ObserverRotation;
	FVector ObserverLocation;
	AMyBuilding* TargetBuilding;
	bool bResearch = false;
	float CurrentPitch;
	void GoToObserverLocation();
	void LookUp(float Value);
	void Turn(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MouseZoom(float Value);
	bool BuildCheck();

	UFUNCTION(BlueprintCallable)
	void BuildingClick();
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float ZoomSense = 30;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float MinSpringLength = 500;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraSense = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float MaxCameraPitch = 50;

	UPROPERTY()
		bool bActiveFreeMode = false;
	
};
