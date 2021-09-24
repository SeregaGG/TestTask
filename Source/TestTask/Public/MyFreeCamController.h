// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyFreeCamController.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API AMyFreeCamController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyFreeCamController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<class UMyUserWidget> MyUserWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMyUserWidget* MyUserWidget;
protected:
	
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	
};
