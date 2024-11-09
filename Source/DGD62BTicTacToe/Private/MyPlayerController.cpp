// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

void AMyPlayerController::BeginPlay()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;


	//find the CameraActor with the tag FixedCamera
	ACameraActor* FixedCameraActor = nullptr;

	//search for the actor with the specified tag
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("FixedCamera"), FoundActors);

	if (FoundActors.Num() > 0) {
		//assume that we only have one camera in our scene
		FixedCameraActor = Cast<ACameraActor>(FoundActors[0]);
	}

	if (FixedCameraActor) {
		//set the view target to the camera actor
		SetViewTargetWithBlend(FixedCameraActor);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Camera Not Found"));
	}





}
