// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "GameBoard.generated.h"

//Enum to represent the state of each cell
UENUM(BlueprintType)
enum class ECellState : uint8 {
	Empty UMETA(DisplayName = "Empty"),
	Cross UMETA(DisplayName = "Cross"),
	Cyclinder UMETA(DisplayName = "Cyclinder")
};


UCLASS()
class DGD62BTICTACTOE_API AGameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCellClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	//Bleuprint references for placing the Cross and the Cyclinder
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	TSubclassOf<class AActor> CrossBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	TSubclassOf<class AActor> CyclinderBlueprint;

	TArray<UBoxComponent*> BoxColliders;

	UFUNCTION()
	void UpdateGameStatus(const FString& NewStatus);

private:
	//3*3 grid to store the state of the board
	ECellState Grid[3][3];

	// current player turn (1 for Cross, 2 for Cyclinder)
	int32 CurrentPlayerTurn;

	//a function that is going to determine which cell was clicked
	FIntPoint GetClickedCell(UPrimitiveComponent* TouchedComponent) const;

	//check for win condition
	bool CheckWinCondition(ECellState player);

	//check for draw condition
	bool CheckDrawCondition();

	//reset the game board
	UFUNCTION()
	void ResetBoard();
};
