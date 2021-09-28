#include "StaticNamespaceTest.h"
#include "FGAI_2/MyStuff/AStar/AStarPathFinder.h"

bool AStar::FHeuristicCalculations::BasicHeuristics(FTileInfo* Info,FDirectionIndex* Direction , FGridCell* Goal)
{
	if(Info->Cell->Type == Wall)
	{
		return false;
	}

	float DirectionalMultiplier = 1.0f;
	if(Direction->Dx != 0 && Direction->Dy != 0)
	{
		DirectionalMultiplier = 1.5f;
	}
		
	const FCellIndex CurrentIndex = Info->Cell->MyIndex;
	const FCellIndex GoalIndex = Goal->MyIndex;

	// Chebyshev distance
	Info->HeuristicValue = FMath::Max(FMath::Abs(CurrentIndex.Row - GoalIndex.Row), FMath::Abs(CurrentIndex.Column - GoalIndex.Column) * 10 ) * DirectionalMultiplier;
	
	return true;
}
