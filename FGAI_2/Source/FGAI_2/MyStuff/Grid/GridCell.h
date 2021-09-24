#pragma once

#include "TileTypes.h"
#include "CellIndex.h"
#include "GridCell.generated.h"

USTRUCT()

struct FGridCell
{
	GENERATED_BODY()
public:

	explicit FGridCell(FVector WorldLocation)
	{
		Location = WorldLocation;
	}

	FGridCell(){}

	void SetNeighbor(FCellIndex Neighbor)
	{
		if(!Neighbors.Contains(Neighbor))
		{
			Neighbors.Add(Neighbor);
		}
	}
	
	UPROPERTY()
	TEnumAsByte<ETileType> Type = Ground;

	UPROPERTY()
	FVector Location;

	FCellIndex MyIndex;
	
	UPROPERTY()
	bool bBlock = false;

	UPROPERTY()
	float PathCostMultiplier = 1.0f;

	TArray<FCellIndex> Neighbors;
	
	FORCEINLINE bool operator==(FGridCell& OtherCell) const
	{
		return Location == OtherCell.Location;
	}

	FORCEINLINE bool operator==(FGridCell* OtherCell) const
	{
		return Location == OtherCell->Location;
	}

	bool CompareTo(FGridCell* OtherCell)const
	{
		return Location == OtherCell->Location;
	}
	
};

struct FTileInfo
{

	FGridCell* Cell;

	float HeuristicValue = 0.0f;
	
	float StepCost = 0.0f;

	FTileInfo* PreviousCell;

	explicit FTileInfo(FGridCell* MyCell)
	{
		Cell = MyCell;
		PreviousCell = nullptr;
	}

	FTileInfo(FGridCell* MyCell, FTileInfo * Previous, const float AccumulatedSteps)
	{
		Cell = MyCell;
		PreviousCell = Previous;
		StepCost = AccumulatedSteps;
	}

	FTileInfo(FGridCell* MyCell, FTileInfo* Previous)
	{
		Cell = MyCell;
		PreviousCell = Previous;
	}

	explicit FTileInfo()
	{
		Cell = nullptr;
		PreviousCell = nullptr;
	}

	FORCEINLINE bool operator==(const FTileInfo &OtherInfo) const
	{
		return Cell == OtherInfo.Cell;
	}

	FORCEINLINE bool operator<(const FTileInfo &Other) const
	{
		return StepCost + HeuristicValue < Other.StepCost + Other.HeuristicValue;
	}
};