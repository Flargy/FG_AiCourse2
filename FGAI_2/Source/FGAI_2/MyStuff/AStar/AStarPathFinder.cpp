#include "AStarPathFinder.h"
#include "DrawDebugHelpers.h"
#include "FGAI_2/MyStuff/Grid/PathingGrid.h"

TArray<FGridCell*> AStar::FAStarPathFinder::GeneratePath(APathingGrid* Grid, const FHeuristicsCalculation HeuristicsFunction,
                                                         FGridCell* Start, FGridCell* Goal)
{
	TArray<FGridCell*> FinalPath;
	FTileInfo test1;
	test1.Cell = Start;
	FTileInfo test2;
	test2.Cell = Goal;
	
	HeuristicsFunction(test1, Start, Goal);

	TArray<FTileInfo> OpenList;
	TArray<FTileInfo> ClosedList;

	OpenList.Add(FTileInfo(Start));

	/*while(OpenList.Num() != 0) // do a* here
	{
		
	}*/


	
	if(Start == Goal)
	{
		UE_LOG(LogTemp, Warning, TEXT("Same ones"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("not same "))
	}

	
	DrawDebugSphere(Grid->GetWorld(), Start->Location + FVector::UpVector * 100.0f, 80.0f, 20, FColor::Purple, false, 20.0f, 0, 8);
	DrawDebugSphere(Grid->GetWorld(), Goal->Location, 80.0f, 20, FColor::Green, false, 20.0f, 0, 8);
	
	return FinalPath;
}

TArray<FGridCell*> AStar::FAStarPathFinder::GeneratePath(APathingGrid* Grid, const FHeuristicsCalculation HeuristicsFunction,
	const FVector Start, const FVector Goal)
{

	if(!Grid->IsWorldLocationInsideGrid(Start) || !Grid->IsWorldLocationInsideGrid(Goal))
	{
		FGridCell ErrorCell;
		ErrorCell.Location = Start;
		TArray<FGridCell*> ReturnCell = {&ErrorCell};
		return ReturnCell;
		
	}

	int i = 0;
	FGridCell* StartCell = Grid->GetCellFromLocation(Start);
	FGridCell* EndCell = Grid->GetCellFromLocation(Goal);

	//UE_LOG(LogTemp, Log, TEXT("Location: X:%f Y:%f"),StartCell.Location.X, StartCell.Location.Y)

	
	return GeneratePath(Grid, HeuristicsFunction, StartCell, EndCell);
}
