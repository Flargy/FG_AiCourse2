#pragma once

#include "TileTypes.h"
#include "CellIndex.h"
#include "GridCell.generated.h"

USTRUCT()
struct FGridCell
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TEnumAsByte<ETileType> Type = Ground;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	float PathCostMultiplier = 1.0f;

	TArray<FCellIndex> Neighbors;
};