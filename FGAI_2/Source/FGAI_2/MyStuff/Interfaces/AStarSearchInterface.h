#pragma once
#include "FGAI_2/MyStuff/Grid/CellIndex.h"
#include "FGAI_2/MyStuff/Grid/GridCell.h"
#include "AStarSearchInterface.generated.h"

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

UINTERFACE(MinimalAPI)
class UAStarSearchInterface : public UInterface
{
	GENERATED_BODY()
};

class IAStarSearchInterface
{
	GENERATED_BODY()

public:

	static int TestFunctionPassing(int Value) // This works for now but I probably dont wanna have it static
	{
		//UE_LOG(LogTemp, Log, TEXT("Value was: %d"), Value)
		return Value;
	}
};