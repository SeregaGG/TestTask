// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFreeCamController.h"
#include "MyUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"
AMyFreeCamController::AMyFreeCamController()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	
}
void AMyFreeCamController::BeginPlay()
{
	Super::BeginPlay();
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	MyUserWidget = CreateWidget<UMyUserWidget>(this, MyUserWidgetClass);
	MyUserWidget->AddToViewport();
	//MyUserWidget->AddToPlayerScreen();
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	
}

void AMyFreeCamController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
}

void AMyFreeCamController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

