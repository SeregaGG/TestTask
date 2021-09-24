// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomCharacter.h"


// Sets default values
ARoomCharacter::ARoomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(32.0f, 96.0f);

	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;
	
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 540.0f;
	GetCharacterMovement()->SetWalkableFloorAngle(60);
}

// Called when the game starts or when spawned
void ARoomCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARoomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ARoomCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ARoomCharacter::LookUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARoomCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARoomCharacter::MoveRight);
	
}

void ARoomCharacter::MoveForward(float Axis)
{
	if (Controller != NULL && Axis != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void ARoomCharacter::MoveRight(float Axis)
{
	if (Controller != NULL && Axis != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void ARoomCharacter::LookUp(float Axis)
{
	AddControllerPitchInput(-Axis);
}

void ARoomCharacter::Turn(float Axis)
{
	AddControllerYawInput(Axis);
}
