#include "StaticNamespaceTest.h"
#include "FGAI_2/MyStuff/AStar/AStarPathFinder.h"

bool AStar::FHeuristicCalculations::BasicHeuristics(FTileInfo* Info, FGridCell* Goal)
{
	if(Info->Cell->Type == Wall)
	{
		return false;
	}

	const FCellIndex CurrentIndex = Info->Cell->MyIndex;
	const FCellIndex GoalIndex = Goal->MyIndex;

	// Chebyshev distance
	Info->HeuristicValue = FMath::Max(FMath::Abs(CurrentIndex.Row - GoalIndex.Row), FMath::Abs(CurrentIndex.Column - GoalIndex.Column) * 10 );
	
	return true;
}
