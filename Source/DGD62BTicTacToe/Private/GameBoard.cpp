// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBoard.h"
#include <Kismet/GameplayStatics.h>
#include <MyGameInstance.h>

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

	//subscribe to the OnResetGameRequested Event
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance) {
		GameInstance->OnResetGameRequested.AddDynamic(this, &AGameBoard::ResetBoard);
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

	//check if the cell is empty
	if (Grid[ClickedCell.X][ClickedCell.Y] == ECellState::Empty) {
		//determine the new state based on the current player
		ECellState NewState = (CurrentPlayerTurn == 1) ? ECellState::Cross : ECellState::Cyclinder;
		Grid[ClickedCell.X][ClickedCell.Y] = NewState;

		//determine which actor to spawn (cross or cyclinder)
		TSubclassOf<AActor> ActorToSpawn = (NewState == ECellState::Cross) ? CrossBlueprint : CyclinderBlueprint;

		FVector Location = TouchedComponent->GetComponentLocation();
		GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, FRotator::ZeroRotator);


		//check for win condition
		if (CheckWinCondition(NewState)) {
			UE_LOG(LogTemp, Warning, TEXT("%s wins!"),
				(NewState == ECellState::Cross) ? TEXT("Cross") : TEXT("Cylinder"));

			UpdateGameStatus((NewState == ECellState::Cross) ? TEXT("Cross Wins") : TEXT("Cylinder wins"));

			return;
		}

		//check for draw condition
		if (CheckDrawCondition()) {
			UE_LOG(LogTemp, Warning, TEXT("It's a draw!!!!"));
			UpdateGameStatus(TEXT("It's a draw"));
			return;
		}



		//switch player turn
		CurrentPlayerTurn = (CurrentPlayerTurn == 1) ? 2 : 1;

	}





}

void AGameBoard::UpdateGameStatus(const FString& NewStatus)
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance) {
		GameInstance->OnGameStatusUpdated.Broadcast(NewStatus);
	}

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
	for (int32 i = 0; i < 3; ++i) {
		//check rows
		if (Grid[i][0] == player && Grid[i][1] == player && Grid[i][2] == player) {
			return true;
		}

		//check columns
		if (Grid[0][i] == player && Grid[1][i] == player && Grid[2][i] == player) {
			return true;
		}
	}

	//check for diagonals
	if (Grid[0][0] == player && Grid[1][1] == player && Grid[2][2] == player) {
		return true;
	}

	if (Grid[0][2] == player && Grid[1][1] == player && Grid[2][0] == player) {
		return true;
	}

	//if no win is found
	return false;




	
}

bool AGameBoard::CheckDrawCondition()
{
	for (int32 Row = 0; Row < 3; ++Row) {
		for (int32 Column = 0; Column < 3; ++Column) {
			if (Grid[Row][Column] == ECellState::Empty) {
				return false; //found an empty cell, not a draw yet
			}
		}
	}

	return true; //no empty cells found, it's a draw
}

void AGameBoard::ResetBoard()
{
	//reset the grid to all empty cells
	for (int32 Row = 0; Row < 3; Row++) {
		for (int32 Column = 0; Column < 3; Column++) {
			Grid[Row][Column] = ECellState::Empty;
		}
	}

	//destroy all spawned actors (crosses and cylinders)
	TArray<AActor*> SpawnedActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), SpawnedActors);

	for (AActor* Actor : SpawnedActors) {
		//check if thea actor is a cross or cylinder
		if (Actor->IsA(CrossBlueprint) || Actor->IsA(CyclinderBlueprint)) {
			Actor->Destroy();
		}
	}

	//reset the player turn back to 1 which is the cross
	CurrentPlayerTurn = 1;
	UE_LOG(LogTemp, Warning, TEXT("Game Board Reset!"));
}

