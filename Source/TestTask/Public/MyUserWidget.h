// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TESTTASK_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* FreeMode;

	UPROPERTY(meta = (BindWidget))
	class UButton* Research;

	UPROPERTY(meta = (BindWidget))
	class UButton* Zoom;

	UPROPERTY(meta = (BindWidget))
	class UButton* UnZoom;

	UPROPERTY(meta = (BindWidget))
	class UButton* EnterTheRoom;
	
	UPROPERTY(meta = (BindWidget))
	class USlider* ChangeParam = nullptr;
	
	FTimerHandle MemberTimerHandle;

	UFUNCTION()
		void EnterTheRoomClicked();
	
	UFUNCTION()
		void AddZoomValue();

	UFUNCTION()
		void StopAddZooming();
	
	UFUNCTION()
		void FreeModeClicked();

	UFUNCTION()
		void ResearchClicked();

	UFUNCTION()
		void ZoomClicked();
	
	UFUNCTION()
		void UnZoomClicked();

	UFUNCTION()
		void StopUnZooming();

	UFUNCTION()
		void SubZoomValue();
	
	UFUNCTION()
		void ChangingParams(float Value);

	UFUNCTION()
		void SetResearchParams();
	
};
