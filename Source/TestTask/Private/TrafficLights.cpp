// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficLights.h"


// Sets default values
ATrafficLights::ATrafficLights()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	FirstRoadStart = CreateDefaultSubobject<UBoxComponent>(TEXT("FirstRoadStart"));
	FirstRoadStart->SetupAttachment(RootComponent);
	FirstRoadStart->InitBoxExtent(FVector(BoxSizeX,BoxSizeY,300));
	FirstRoadStart->SetRelativeLocation(FVector(CrossroadRadius,0,0));
	LightFirstStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightFirstStart"));
	LightFirstStart->SetupAttachment(FirstRoadStart);
	LightFirstStart->SetRelativeLocation(FVector(0,0,HeightLights));
	
	
	
	FirstRoadEnd = CreateDefaultSubobject<UBoxComponent>(TEXT("FirstRoadEnd"));
	FirstRoadEnd->SetupAttachment(RootComponent);
	FirstRoadEnd->InitBoxExtent(FVector(BoxSizeX,BoxSizeY,300));
	FirstRoadEnd->SetRelativeLocation(FVector(-CrossroadRadius,0,0));
	LightFirstEnd = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightFirstEnd"));
	LightFirstEnd->SetupAttachment(FirstRoadEnd);
	LightFirstEnd->SetRelativeLocation(FVector(0,0,HeightLights));
	
	
	
	SecondRoadStart = CreateDefaultSubobject<UBoxComponent>(TEXT("SecondRoadStart"));
	SecondRoadStart->SetupAttachment(RootComponent);
	SecondRoadStart->InitBoxExtent(FVector(BoxSizeY,BoxSizeX,300));
	SecondRoadStart->SetRelativeLocation(FVector(0,CrossroadRadius,0));
	LightSecondStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightSecondStart"));
	LightSecondStart->SetupAttachment(SecondRoadStart);
	LightSecondStart->SetRelativeLocation(FVector(0,0,HeightLights));
	
	
	SecondRoadEnd = CreateDefaultSubobject<UBoxComponent>(TEXT("SecondRoadEnd"));
	SecondRoadEnd->SetupAttachment(RootComponent);
	SecondRoadEnd->InitBoxExtent(FVector(BoxSizeY,BoxSizeX,300));
	SecondRoadEnd->SetRelativeLocation(FVector(0,-CrossroadRadius,0));
	LightSecondEnd = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightSecondEnd"));
	LightSecondEnd->SetupAttachment(SecondRoadEnd);
	LightSecondEnd->SetRelativeLocation(FVector(0,0,HeightLights));

	OnMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OnMaterial"));
	OffMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OffMaterial"));


}

// Called when the game starts or when spawned
void ATrafficLights::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle MyTimerHandle;
	FirstRoadStart->OnComponentBeginOverlap.AddDynamic(this, &ATrafficLights::OnFirstOverlapBegin);
	FirstRoadStart->OnComponentEndOverlap.AddDynamic(this, &ATrafficLights::OnFirstOverlapEnd);
	FirstRoadEnd->OnComponentBeginOverlap.AddDynamic(this, &ATrafficLights::OnFirstOverlapBegin);
	FirstRoadEnd->OnComponentEndOverlap.AddDynamic(this, &ATrafficLights::OnFirstOverlapEnd);
	SecondRoadStart->OnComponentBeginOverlap.AddDynamic(this, &ATrafficLights::OnSecondOverlapBegin);
	SecondRoadStart->OnComponentEndOverlap.AddDynamic(this, &ATrafficLights::OnSecondOverlapEnd);
	SecondRoadEnd->OnComponentBeginOverlap.AddDynamic(this, &ATrafficLights::OnSecondOverlapBegin);
	SecondRoadEnd->OnComponentEndOverlap.AddDynamic(this, &ATrafficLights::OnSecondOverlapEnd);
	
	bCanDriveFirst = RedLight;
	bCanDriveSecond = !RedLight;
	
	if(bCanDriveFirst)
	{
		LightFirstStart->SetMaterial(0, OnMaterial);
		LightFirstEnd->SetMaterial(0, OnMaterial);
		
		LightSecondStart->SetMaterial(0, OffMaterial);
		LightSecondEnd->SetMaterial(0, OffMaterial);
	}
	else
	{
		LightFirstStart->SetMaterial(0, OffMaterial);
		LightFirstEnd->SetMaterial(0, OffMaterial);
		
		LightSecondStart->SetMaterial(0, OnMaterial);
		LightSecondEnd->SetMaterial(0, OnMaterial);
	}
	
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ATrafficLights::SwitchLight, 5.0f, true, 0.0f);

}

// Called every frame
void ATrafficLights::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrafficLights::SwitchLight()
{
	bCanDriveFirst = bCanDriveSecond;
	bCanDriveSecond = !bCanDriveFirst;
	
	if(bCanDriveFirst)
	{
		LightFirstStart->SetMaterial(0, OnMaterial);
		LightFirstEnd->SetMaterial(0, OnMaterial);
		
		LightSecondStart->SetMaterial(0, OffMaterial);
		LightSecondEnd->SetMaterial(0, OffMaterial);
	}
	else
	{
		LightFirstStart->SetMaterial(0, OffMaterial);
		LightFirstEnd->SetMaterial(0, OffMaterial);
		
		LightSecondStart->SetMaterial(0, OnMaterial);
		LightSecondEnd->SetMaterial(0, OnMaterial);
	}
}

void ATrafficLights::OnFirstOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ATrafficLights::OnFirstOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ATrafficLights::OnSecondOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ATrafficLights::OnSecondOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}


