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

	UPROPERTY()
	bool bBlock = false;

	UPROPERTY()
	float PathCostMultiplier = 1.0f;

	TArray<FCellIndex> Neighbors;
};