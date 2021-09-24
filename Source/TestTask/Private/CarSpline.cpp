// Fill out your copyright notice in the Description page of Project Settings.


#include "CarSpline.h"

#include "TrafficLights.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ACarSpline::ACarSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

		
	CarMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	CarMeshComponent->SetupAttachment(RootComponent);
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->InitBoxExtent(FVector(100, 100, 100));

}

// Called when the game starts or when spawned
void ACarSpline::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentHit.AddDynamic(this,&ACarSpline::OnHit);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this,  &ACarSpline::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACarSpline::OnOverlapEnd);
	if(BeginPlayCarMesh)
		CarMeshComponent->SetStaticMesh(BeginPlayCarMesh);
}

// Called every frame
void ACarSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CarRiding();

	FHitResult OutHit;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + GetActorForwardVector() * 150;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
	UBoxComponent* CurrentStopLine = Cast<UBoxComponent>(OutHit.GetComponent());
	ACarSpline* OtherCar = Cast<ACarSpline>(OutHit.GetActor());

	if(OtherCar)
	{
		if(OtherCar->CurrentSpeed < CurrentSpeed)
		{
			DoCarStop();
			return;
		}
	}
	
	if(CurrentStopLine && !bOnCrossroad)
	{
		if(CurrentStopLine->GetName() == "FirstRoadStart" || CurrentStopLine->GetName() == "FirstRoadEnd")
		{
			ATrafficLights* CurrentTL = Cast<ATrafficLights>(CurrentStopLine->GetOwner());
			bStopLight = !CurrentTL->bCanDriveFirst;
		}
		else if(CurrentStopLine->GetName() == "SecondRoadStart" || CurrentStopLine->GetName() == "SecondRoadEnd")
		{
			ATrafficLights* CurrentTL = Cast<ATrafficLights>(CurrentStopLine->GetOwner());
			bStopLight = !CurrentTL->bCanDriveSecond;
		}
	}


	
	
	if(!bStopLight)
	{
		if(CurrentSpeed < MaxSpeed)
			DoCarAcceleration();
	}
	else
	{
		if(CurrentSpeed > 0)
		{
			DoCarStop();
		}
	}
}


void ACarSpline::dsa()
{
	
}

void ACarSpline::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(bStopLight));
}


void ACarSpline::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<ACarSpline>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(bOnCrossroad));
		bOnCrossroad++;
	}
}

void ACarSpline::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(!Cast<ACarSpline>(OtherActor))
	{
		bOnCrossroad++;
		if(bOnCrossroad == 4)
			bOnCrossroad = 0;
	}
}



void ACarSpline::DoCarAcceleration()
{
	CurrentSpeed += Acceleration;

	if(CurrentSpeed > MaxSpeed)
		CurrentSpeed = MaxSpeed;
}

void ACarSpline::DoCarStop()
{
	CurrentSpeed -= StopSpeedDelta;

	if(CurrentSpeed <= 0)
		CurrentSpeed = 0;
}



void ACarSpline::CarRiding()
{
	if(SplineActorRoad)
	{
		CurrentDistance += CurrentSpeed * GetWorld()->GetDeltaSeconds();
	
		FVector NewLocation = SplineActorRoad->CarSplineRoad->GetLocationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);
		SetActorLocation(NewLocation);
	
		FVector Direction = SplineActorRoad->CarSplineRoad->GetDirectionAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);
		SetActorRotation(Direction.Rotation());

		if (CurrentDistance >= SplineActorRoad->CarSplineRoad->GetSplineLength())
			CurrentDistance = 0;
	}
}

void ACarSpline::SpawnSpline()
{
	if(ActorWithSplineClass)
		SplineActorRoad = GetWorld()->SpawnActor<AActorWithSpline>(ActorWithSplineClass, GetActorLocation(), GetActorRotation());
}