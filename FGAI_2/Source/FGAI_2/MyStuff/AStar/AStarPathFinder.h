#pragma once
#include "FGAI_2/MyStuff/Grid/GridCell.h"

class APathingGrid;
struct FTileInfo;
namespace AStar
{

	class FAStarPathFinder
	{

	public:
		typedef TFunction<bool(FTileInfo, FGridCell*, FGridCell*)> FHeuristicsCalculation;
	
		static TArray<FGridCell*> GeneratePath(APathingGrid* Grid, FHeuristicsCalculation HeuristicsFunction, FGridCell* Start, FGridCell* Goal);

		static TArray<FGridCell*> GeneratePath(APathingGrid* Grid, FHeuristicsCalculation HeuristicsFunction, FVector Start, FVector Goal);


		float StepCost = 1000.0f;
	};
}