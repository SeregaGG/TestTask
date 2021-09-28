// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

#include <string>

#include "MyFreeCam.h"
#include "MyFreeCamController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

bool UMyUserWidget::Initialize()
{
	Super::Initialize();
	FreeMode->OnClicked.AddDynamic(this, &UMyUserWidget::FreeModeClicked);
	Research->OnClicked.AddDynamic(this, &UMyUserWidget::ResearchClicked);
	EnterTheRoom->OnClicked.AddDynamic(this, &UMyUserWidget::EnterTheRoomClicked);

	
	Zoom->OnPressed.AddDynamic(this, &UMyUserWidget::ZoomClicked);
	Zoom->OnReleased.AddDynamic(this, &UMyUserWidget::StopAddZooming);
	
	UnZoom->OnPressed.AddDynamic(this, &UMyUserWidget::UnZoomClicked);
	UnZoom->OnReleased.AddDynamic(this, &UMyUserWidget::StopUnZooming);
	
	ChangeParam->OnValueChanged.AddDynamic(this, &UMyUserWidget::ChangingParams);
	return true;
}

void UMyUserWidget::EnterTheRoomClicked()
{
	AMyFreeCam* TempMyFreeCam = Cast<AMyFreeCam>(GetOwningPlayerPawn());
	if(TempMyFreeCam)
	{
		if(TempMyFreeCam->TargetBuilding)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "Room");
		}
	}
}


void UMyUserWidget::ChangingParams(float Value)
{
	AMyFreeCam* TempMyFreeCam = Cast<AMyFreeCam>(GetOwningPlayerPawn());
	if(TempMyFreeCam)
	{
		if(TempMyFreeCam->TargetBuilding)
		{
			TempMyFreeCam->TargetBuilding->MyMaterial->SetScalarParameterValue(TEXT("ColorBlend"), Value);
		}
	}
}


void UMyUserWidget::ResearchClicked()
{
	AMyFreeCam* TempMyFreeCam = Cast<AMyFreeCam>(GetOwningPlayerPawn());
	if(TempMyFreeCam->TargetBuilding)
	{
		TempMyFreeCam->TargetBuilding->TriggerBox->SetCollisionProfileName(TEXT("SpringArmCollision"));
		TempMyFreeCam->TargetBuilding->BuildingMesh->SetCollisionProfileName(TEXT("SpringArmCollision"));
		FLatentActionInfo ActionInfo;
		ActionInfo.CallbackTarget = this;
		FVector CamDirection = (TempMyFreeCam->TargetBuilding->GetActorLocation() - TempMyFreeCam->TargetBuilding->GlobalTargetLocation);
		UKismetSystemLibrary::MoveComponentTo(TempMyFreeCam->GetRootComponent(),TempMyFreeCam->TargetBuilding->GlobalTargetLocation,CamDirection.Rotation(),false, false, 3.f,true,EMoveComponentAction::Move, ActionInfo);
		FTimerHandle FlyTimer;
		GetWorld()->GetTimerManager().SetTimer(FlyTimer, this, &UMyUserWidget::SetResearchParams, 3.f, false);
		/*TempMyFreeCam->SetActorLocation(TempMyFreeCam->TargetBuilding->GetActorLocation());
		TempMyFreeCam->CameraBoom->TargetArmLength = CamDirection.Size();
		TempMyFreeCam->bResearch = true;
		TempMyFreeCam->bActiveFreeMode = false;*/
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, CapsuleComponent->GetComponentLocation().ToString());
	}
}

void UMyUserWidget::SetResearchParams()
{
	AMyFreeCam* TempMyFreeCam = Cast<AMyFreeCam>(GetOwningPlayerPawn());
	TempMyFreeCam->SetActorLocation(TempMyFreeCam->TargetBuilding->GetActorLocation());
	FVector CamDirection = (TempMyFreeCam->TargetBuilding->GetActorLocation() - TempMyFreeCam->TargetBuilding->GlobalTargetLocation);
	TempMyFreeCam->CameraBoom->TargetArmLength = CamDirection.Size();
	TempMyFreeCam->GetController()->SetControlRotation(CamDirection.Rotation());
	TempMyFreeCam->bResearch = true;
	TempMyFreeCam->bActiveFreeMode = false;
}


void UMyUserWidget::ZoomClicked()
{

	
	AMyFreeCam* TempMyFreeCam = Cast<AMyFreeCam>(GetOwningPlayerPawn());

	if(TempMyFreeCam->bResearch)
	{
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &UMyUserWidget::AddZoomValue, 0.01f, true);
	}
}

void UMyUserWidget::AddZoomValue()
{
	AMyFreeCam* TempMyFreeCam = Cast<AMyFreeCam>(GetOwningPlayerPawn());

		
	FHitResult OutHit;
	FVector TraceStart = TempMyFreeCam->FollowCamera->GetComponentLocation();
	FVector TraceEnd = TraceStart + TempMyFreeCam->FollowCamera->GetForwardVector() * 100;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(TempMyFreeCam);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd,ECollisionChannel::ECC_WorldStatic, CollisionQueryParams);
	if(!bHit)
	{
		TempMyFreeCam->CameraBoom->TargetArmLength-=10;
	}
}
void UMyUserWidget::StopAddZooming()
{
	GetWorld()->GetTimerManager().ClearTimer(MemberTimerHandle);
}


void UMyUserWidget::FreeModeClicked()
{
	AMyFreeCam* TempMyFreeCam = Cast<AMyFreeCam>(GetOwningPlayerPawn());
	if(TempMyFreeCam)
	{
		APlayerController* TempController = Cast<APlayerController>(TempMyFreeCam->GetController());
	
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(TempController);
		TempMyFreeCam->EnableInput(TempController);

		if(TempMyFreeCam->TargetBuilding)
		{
			TempMyFreeCam->TargetBuilding->TriggerBox->SetCollisionProfileName(TEXT("BlockAll"));
			TempMyFreeCam->TargetBuilding->BuildingMesh->SetCollisionProfileName(TEXT("BlockAll"));
		}
	
		TempController->bShowMouseCursor = false;
		TempController->bEnableClickEvents = false;
	
		TempMyFreeCam->bActiveFreeMode = true;
		if(TempMyFreeCam->bResearch)
		{
			TempMyFreeCam->SetActorLocation(TempMyFreeCam->FollowCamera->GetComponentLocation());
			TempMyFreeCam->CameraBoom->TargetArmLength = 0;
			TempMyFreeCam->bResearch = false;
		}
	}
}

void UMyUserWidget::UnZoomClicked()
{
	AMyFreeCam* TempMyFreeCam = Cast<AMyFreeCam>(GetOwningPlayerPawn());
	if(TempMyFreeCam->bResearch)
	{
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &UMyUserWidget::SubZoomValue, 0.01f, true);
	}
}
 void UMyUserWidget::SubZoomValue()
 {
	AMyFreeCam* TempMyFreeCam = Cast<AMyFreeCam>(GetOwningPlayerPawn());
	TempMyFreeCam->CameraBoom->TargetArmLength+=10;
 }

void UMyUserWidget::StopUnZooming()
{
	GetWorld()->GetTimerManager().ClearTimer(MemberTimerHandle);
}
