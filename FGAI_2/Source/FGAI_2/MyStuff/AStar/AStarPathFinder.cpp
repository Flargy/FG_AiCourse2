#include "AStarPathFinder.h"
#include "DrawDebugHelpers.h"
#include "FGAI_2/MyStuff/Grid/PathingGrid.h"

TArray<FGridCell*> AStar::FAStarPathFinder::GeneratePath(APathingGrid* Grid, const FHeuristicsCalculation HeuristicsFunction,
                                                         FGridCell* Start, FGridCell* Goal)
{

	// TODO: something is wrong when you take too many steps
	TArray<FGridCell*> FinalPath;

	TArray<FTileInfo> OpenList;
	TArray<FTileInfo> ClosedList;
	ClosedList.SetNum(Grid->GetNumTiles()); // builds the array at maximum size so that the memory never gets shifted
	int ClosedCounter = 0;
	FTileInfo End;

	OpenList.Add(FTileInfo(Start));

	const float StepCost = 2.0f;
	
	while(OpenList.Num() > 0) 
	{
		if(OpenList[0].Cell == Goal)
		{
			UE_LOG(LogTemp, Warning, TEXT("goal found"))
			End = OpenList[0];
			break;
		}
		
		FTileInfo Parent = OpenList[0];
		
		OpenList.RemoveAt(0);
		ClosedList[ClosedCounter] = Parent;
		for (FCellIndex Index : Parent.Cell->Neighbors)
		{
			FTileInfo Neighbor = FTileInfo(Grid->GetCellFromIndex(Index), &ClosedList[ClosedCounter]);

			Neighbor.StepCost = Parent.StepCost + StepCost; // gives it the step value

			if(HeuristicsFunction(&Neighbor, &Index.Direction, Goal) && !ClosedList.Contains(Neighbor))
			{
				if(!OpenList.Contains(Neighbor))
				{
					OpenList.Add(Neighbor);
					continue;
				}
				int i = 0;
				for (auto Tile : OpenList)
				{
					if(Tile == Neighbor)
					{
						break;
					}
					i++;
				}
				
				if(OpenList[i].StepCost > Neighbor.StepCost)
				{
					OpenList.Remove(Neighbor);
					OpenList.Add(Neighbor);
				}
			
			}
		}
		
		ClosedCounter++;
		OpenList.Sort(); // sorts the list
	}

	if(OpenList.Num() == 0)
	{
		// we didn't find the path and something is wrong
		FinalPath.Add(Start);
		return FinalPath;
	}
	OpenList.Empty(); // Free up the space cause we dont need it anymore
	
	FinalPath = BuildFinalPath(&End);

	for (auto Cell : FinalPath)
	{
		DrawDebugSphere(Grid->GetWorld(), Cell->Location + FVector::UpVector * 100.0f, 80.0f, 20, FColor::Red, false, 20.0f, 0, 8);
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

TArray<FGridCell*> AStar::FAStarPathFinder::BuildFinalPath(FTileInfo* CellInfo, TArray<FGridCell*> FinalPath)
{
	if(CellInfo->PreviousCell == nullptr)
	{
		return FinalPath;
	}
	if(CellInfo->Cell == nullptr)
	{
		return FinalPath;
	}
	FinalPath.Add(CellInfo->Cell);
	return BuildFinalPath(CellInfo->PreviousCell, FinalPath);
}

TArray<FGridCell*> AStar::FAStarPathFinder::BuildFinalPath(FTileInfo* CellInfo)
{
	TArray<FGridCell*> FinalPath;

	return BuildFinalPath(CellInfo, FinalPath);
}
