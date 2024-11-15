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
			//add dynamic event binding
			BoxCollider->OnClicked.AddDynamic(this, &AGameBoard::OnCellClicked);

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
	//print the clicked component
	UE_LOG(LogTemp, Warning, TEXT("Touched Component: %s"), *TouchedComponent->GetName());
	FIntPoint ClickedCell = GetClickedCell(TouchedComponent);
	UE_LOG(LogTemp, Warning, TEXT("Cell Clicked: %d %d"), ClickedCell.X, ClickedCell.Y);
}

void AGameBoard::UpdateGameStatus(const FString& NewStatus)
{
}

FIntPoint AGameBoard::GetClickedCell(UPrimitiveComponent* TouchedComponent) const
{
	FString ComponentName = TouchedComponent->GetName();

	//extract the row and column from the name (assume that components are named in the following format
	//BoxCollision_1_1, BoxCollision_1_2 etc

	//extract the row and column from the component name
	int32 Row = -1, Column = -1;
	FString LeftPart, RightPart;
	if (ComponentName.Split(TEXT("_"), nullptr, &RightPart))
	{
		if (RightPart.Split(TEXT("_"), &LeftPart, &RightPart)) {
			Row = FCString::Atoi(*LeftPart);
			Column = FCString::Atoi(*RightPart);
		}
	}

	return FIntPoint(Row-1,Column-1); //convert to zero-based index
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

