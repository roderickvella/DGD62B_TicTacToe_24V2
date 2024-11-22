// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetGameRequested);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStatusUpdated, const FString&, NewStatus);


UCLASS()
class DGD62BTICTACTOE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	//delegates that are accessible globally
	UPROPERTY(BlueprintCallable, Category = "Game Events")
	FOnResetGameRequested OnResetGameRequested;

	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnGameStatusUpdated OnGameStatusUpdated;

};
