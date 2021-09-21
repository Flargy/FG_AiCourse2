#pragma once
/*#include "FGAI_2/MyStuff/Grid/CellIndex.h"
#include "FGAI_2/MyStuff/Grid/PathingGrid.h"*/
#include "HeuristicInterface.generated.h"

/*USTRUCT(BlueprintType)
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
};*/

UINTERFACE(MinimalAPI)
class UHeuristicInterface : public UInterface
{
	GENERATED_BODY()
};

class IHeuristicInterface
{
	GENERATED_BODY()
public:

	UFUNCTION()
	virtual	int TestFunctionPassing(int Value) = 0;
	
};