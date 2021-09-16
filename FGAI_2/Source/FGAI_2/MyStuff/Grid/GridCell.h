#pragma once

#include "TileTypes.h"
#include "CellIndex.h"
#include "GridCell.generated.h"

USTRUCT(BlueprintType)
struct FGridCell
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TEnumAsByte<ETileType> Type = Ground;

	UPROPERTY()
	FVector Location;

	UPROPERTY(BlueprintReadWrite, Category = "Tile")
	bool bBlock = false;

	UPROPERTY()
	float PathCostMultiplier = 1.0f;

	TArray<FCellIndex> Neighbors;
};