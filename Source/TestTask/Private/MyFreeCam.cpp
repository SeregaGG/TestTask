// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFreeCam.h"

#include "MyFreeCamController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AMyFreeCam::AMyFreeCam()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->InitCapsuleSize(32,32);
	RootComponent = CapsuleComponent;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 0.f;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetupAttachment(CameraBoom);


	
	MyMovementComponentComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MoveComp"));
	MyMovementComponentComp->SetUpdatedComponent(RootComponent);
	MyMovementComponentComp->TurningBoost = 100;
}

// Called when the game starts or when spawned
void AMyFreeCam::BeginPlay()
{
	Super::BeginPlay();

	MyMovementComponentComp->MaxSpeed = CameraSpeed;
	MyMovementComponentComp->Acceleration = CameraSpeed * 5;
	MyMovementComponentComp->Deceleration = CameraSpeed * 5;
	CurrentPitch =  GetActorForwardVector().Rotation().Pitch;
	
	ObserverLocation = GetActorLocation();
	ObserverRotation = GetController()->GetControlRotation();
	MaxCameraPitch = -MaxCameraPitch;
	/*if(Cast<AMyFreeCamController>(GetController())->bShowMouseCursor)
		DisableInput(Cast<APlayerController>(GetController()));*/
	
}

// Called every frame
void AMyFreeCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if(!bActiveFreeMode)
		DisableInput(Cast<APlayerController>(GetController()));
		*/
}


// Called to bind functionality to input
void AMyFreeCam::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("BuildingClick",EInputEvent::IE_Released,this,&AMyFreeCam::BuildingClick);
	
	PlayerInputComponent->BindAction("GoToObserverLocation",EInputEvent::IE_Pressed,this,&AMyFreeCam::GoToObserverLocation);
	
	PlayerInputComponent->BindAxis("LookUp",this,&AMyFreeCam::LookUp);
	PlayerInputComponent->BindAxis("Turn",this,&AMyFreeCam::Turn);
	
	PlayerInputComponent->BindAxis("MoveForward",this,&AMyFreeCam::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&AMyFreeCam::MoveRight);

	PlayerInputComponent->BindAxis("MouseZoom",this,&AMyFreeCam::MouseZoom);
}

void AMyFreeCam::GoToObserverLocation()
{
	if(TargetBuilding)
	{
		TargetBuilding->TriggerBox->SetCollisionProfileName(TEXT("BlockAll"));
		TargetBuilding->BuildingMesh->SetCollisionProfileName(TEXT("BlockAll"));
	}
	GetController()->SetControlRotation(ObserverRotation);
	SetActorLocation(ObserverLocation);
	
	CameraBoom->TargetArmLength = 0;
	bResearch = false;
	bActiveFreeMode = false;
	Cast<AMyFreeCamController>(GetController())->bShowMouseCursor = true;
}


void AMyFreeCam::BuildingClick()
{
	if(bResearch)
		return;
	if(Cast<AMyFreeCamController>(GetController())->bShowMouseCursor)
	{
		FHitResult HitResult;
		//TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		//bool bHit =Cast<AMyFreeCamController>(GetController())->GetHitResultUnderCursorForObjects(ObjectTypes,false,HitResult);
		bool bHit = Cast<AMyFreeCamController>(GetController())->GetHitResultUnderCursor(ECC_Visibility, true,HitResult);
	
		if(bHit)
		{
			if(Cast<AMyBuilding>(HitResult.GetActor()))
			{
				TargetBuilding = Cast<AMyBuilding>(HitResult.GetActor());
				
			}
		}
	}
}

void AMyFreeCam::MouseZoom(float Value)
{
	if(bResearch && CameraBoom->TargetArmLength)
	{
		if(FVector::DistXY(FollowCamera->GetComponentLocation(), TargetBuilding->GetActorLocation()) > MinSpringLength && Value > 0)
		{
			CameraBoom->TargetArmLength-= (Value * ZoomSense);
			
		}
		else if(Value < 0)
			CameraBoom->TargetArmLength-= (Value * ZoomSense);
	}
}


void AMyFreeCam::LookUp(float Value)
{
	if(bResearch)
	{
		if((GetActorRotation().Pitch + Value) > MaxCameraPitch)
		{
			if(FVector::DistXY(FollowCamera->GetComponentLocation(), TargetBuilding->GetActorLocation()) > MinSpringLength && Value > 0)
				AddControllerPitchInput(-Value);
			else if(Value<0)
				AddControllerPitchInput(-Value);
		}
		else
			GetController()->SetControlRotation(FRotator(MaxCameraPitch, GetActorRotation().Yaw,GetActorRotation().Roll));
		
		return;
	}
	
	if(bActiveFreeMode)
	{
		AddControllerPitchInput(-Value);
	}
}

bool AMyFreeCam::BuildCheck()
{
	FHitResult OutHit;
	FVector TraceStart = FollowCamera->GetComponentLocation();
	FVector TraceEnd = TraceStart + FollowCamera->GetForwardVector() * 100;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	bool bHit = false;
	GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd,ECollisionChannel::ECC_WorldStatic, CollisionQueryParams);
	if(Cast<AMyBuilding>(OutHit.GetActor()))
	{
		bHit = true;
	}
	
	return bHit;
}


void AMyFreeCam::Turn(float Value)
{
	if(bResearch && FVector::DistXY(FollowCamera->GetComponentLocation(), TargetBuilding->GetActorLocation()) > MinSpringLength)
	{
		AddControllerYawInput(Value);
	}

	if(bActiveFreeMode)
	{
		AddControllerYawInput(Value);
	}
}

void AMyFreeCam::MoveForward(float Value)
{
	if(!bActiveFreeMode)
		return;
	AddMovementInput(FollowCamera->GetForwardVector(), Value);
}

void AMyFreeCam::MoveRight(float Value)
{
	if(!bActiveFreeMode)
		return;
	AddMovementInput(FollowCamera->GetRightVector(), Value);
}
