#pragma once

#include "GameFramework/Actor.h"
#include "GridCell.h"
#include "PathingGrid.generated.h"

USTRUCT(BlueprintType)
struct FTileInfo
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FGridCell Cell;

	UPROPERTY()
	float DistanceToGoal;

	UPROPERTY()
	float TotalCost;

	UPROPERTY()
	FCellIndex PreviousCell;
};

UCLASS()
class APathingGrid : public AActor
{
	GENERATED_BODY()

#pragma region UnrealSpecificFunctions
	
	APathingGrid();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

#pragma endregion

public:

#pragma region Variables
	UPROPERTY(EditInstanceOnly)
	int Rows = 5;

	UPROPERTY(EditInstanceOnly)
	int Columns = 5;

	UPROPERTY(EditInstanceOnly)
	int CellSize = 50;

	UPROPERTY(EditInstanceOnly)
	int CellMargin = 5;

	UPROPERTY(EditInstanceOnly)
	float BaseMovementCost = 500.f;

#pragma endregion

#pragma region Functions

	TArray<FGridCell> GeneratePath(FVector StartingLocation, FVector EndLocation); // add agent type to this later

	FGridCell GetCellFromVector(FVector Location);

	FGridCell GetCellFromIndex(FCellIndex Index);
	
#pragma endregion

private:

#pragma region Variables

	UPROPERTY(Transient)
	TArray<FGridCell> AllCells;
	
#pragma endregion 

#pragma region Functions

	void BuildGrid();
	
	void AssignNeighbors(int Row, int Column);
	
#pragma endregion 
};