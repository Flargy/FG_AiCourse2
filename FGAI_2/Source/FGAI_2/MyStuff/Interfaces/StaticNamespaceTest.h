#pragma once
#include "FGAI_2/MyStuff/AStar/AStarPathFinder.h"


namespace AStar
{
	
	class FHeuristicCalculations
	{
	public:
		static bool BasicHeuristics(FTileInfo* Info, FGridCell* Goal);
	};

}