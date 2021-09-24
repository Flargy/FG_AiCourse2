#pragma once
#include "FGAI_2/MyStuff/Grid/GridCell.h"

class APathingGrid;
struct FTileInfo;
namespace AStar
{

	class FAStarPathFinder
	{

	public:
		typedef TFunction<bool(FTileInfo*, FGridCell*)> FHeuristicsCalculation;
	
		static TArray<FGridCell*> GeneratePath(APathingGrid* Grid, FHeuristicsCalculation HeuristicsFunction, FGridCell* Start, FGridCell* Goal);

		static TArray<FGridCell*> GeneratePath(APathingGrid* Grid, FHeuristicsCalculation HeuristicsFunction, FVector Start, FVector Goal);

	private:
		static TArray<FGridCell*> BuildFinalPath(FTileInfo* CellInfo);

		static TArray<FGridCell*> BuildFinalPath(FTileInfo* TileInfo, TArray<FGridCell*>);
	};
}