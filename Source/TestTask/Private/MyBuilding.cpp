// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBuilding.h"
#include "MyFreeCam.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyBuilding::AMyBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(RootComponent);
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->OnReleased.AddDynamic(this, &AMyBuilding::MyOnReleased);
}

// Called when the game starts or when spawned
void AMyBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	MyMaterial = UMaterialInstanceDynamic::Create(BuildingMesh->GetMaterial(0),nullptr);
	if(MyMaterial)
	{
		BuildingMesh->SetMaterial(0, MyMaterial);
	}
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}
void AMyBuilding::MyOnReleased(UPrimitiveComponent* OtherComp, FKey ReleasedKey)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherComp->GetName());
}

// Called every frame
void AMyBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

