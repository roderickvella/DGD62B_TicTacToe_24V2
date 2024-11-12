// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBoard.h"

// Sets default values
AGameBoard::AGameBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameBoard::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GameBoard BeginPlay"));

	//set the grid to all empty cells
	for (int32 Row = 0; Row < 3; ++Row) {
		for (int32 Col = 0; Col < 3; ++Col) {
			Grid[Row][Col] = ECellState::Empty;
		}
	}

	//set the current player turn to cross (1)
	CurrentPlayerTurn = 1;

	//auto fill BoxColliders array with all UBoxComponent instances attached to this actor
	GetComponents<UBoxComponent>(BoxColliders);

	for (UBoxComponent* BoxCollider : BoxColliders) {
		if (BoxCollider) {
			UE_LOG(LogTemp, Warning, TEXT("Box Collider: %s"), *BoxCollider->GetName());
		}
	}
}

// Called every frame
void AGameBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameBoard::OnCellClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{

}

void AGameBoard::UpdateGameStatus(const FString& NewStatus)
{
}

FIntPoint AGameBoard::GetClickedCell(UPrimitiveComponent* TouchedComponent) const
{
	return FIntPoint();
}

bool AGameBoard::CheckWinCondition(ECellState player)
{
	return false;
}

bool AGameBoard::CheckDrawCondition()
{
	return false;
}

void AGameBoard::ResetBoard()
{
}

