#include "AStarPathFinder.h"
#include "DrawDebugHelpers.h"
#include "FGAI_2/MyStuff/Grid/PathingGrid.h"

TArray<FGridCell*> AStar::FAStarPathFinder::GeneratePath(APathingGrid* Grid, const FHeuristicsCalculation HeuristicsFunction,
                                                         FGridCell* Start, FGridCell* Goal)
{

	// TODO: make diagonal movement more expensive
	TArray<FGridCell*> FinalPath;

	TArray<FTileInfo> OpenList;
	TArray<FTileInfo> ClosedList;

	OpenList.Add(FTileInfo(Start));

	const float StepCost = 20.0f;
	
	while(OpenList.Num() > 0) // do A* here
	{
		if(OpenList[0].Cell == Goal)
		{
			UE_LOG(LogTemp, Warning, TEXT("goal found"))
			break;
		}
		
		FTileInfo Parent = OpenList[0];
		
		OpenList.RemoveAt(0);
		ClosedList.Add(Parent);
		
		for (FCellIndex Index : Parent.Cell->Neighbors)
		{
			FTileInfo Neighbor = FTileInfo(Grid->GetCellFromIndex(Index), &ClosedList.Top());

			
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
		

		OpenList.Sort(); // sorts the list
	}

	if(OpenList[0].Cell != Goal)
	{
		// we didn't find the path and something is wrong
		FinalPath.Add(Start);
		return FinalPath;
	}


	FinalPath = BuildFinalPath(&OpenList[0]);

	FTileInfo* TileToTest = &OpenList[0];

	for (auto Cell : FinalPath)
	{
		UE_LOG(LogTemp, Log, TEXT("Counter"))
		DrawDebugSphere(Grid->GetWorld(), Cell->Location + FVector::UpVector * 100.0f, 80.0f, 20, FColor::Red, false, 20.0f, 0, 8);
	}

	/*for (int i = 0; i < FinalPath.Num() - 1; i++)
	{
		DrawDebugSphere(Grid->GetWorld(), FinalPath[i]->Location + FVector::UpVector * 100.0f, 80.0f, 20, FColor::Red, false, 20.0f, 0, 8);
	}*/

	/*if(OpenList[0].PreviousCell == &OpenList[0])
	{
		UE_LOG(LogTemp, Log, TEXT("Fuck"))
	}*/

	/*for (auto Path : ClosedList)
	{
		if(Path.PreviousCell != nullptr)
		UE_LOG(LogTemp, Log, TEXT("Tile value: %f"), Path.PreviousCell->StepCost)
		DrawDebugSphere(Grid->GetWorld(), Path.Cell->Location + FVector::UpVector * 100.0f, 80.0f, 20, FColor::Blue, false, 40.0f, 0, 8);
	}*/


	/*for (int i = 0; i < 12; i++)
	{
		if(TileToTest == nullptr)
		{
			break;
		}
		//UE_LOG(LogTemp, Log, TEXT("Tile value: %f"), TileToTest->HeuristicValue)
		DrawDebugSphere(Grid->GetWorld(), TileToTest->Cell->Location + FVector::UpVector * 100.0f, 80.0f, 20, FColor::Red, false, 20.0f, 0, 8);
		TileToTest = TileToTest->PreviousCell;

	}*/
	

	/*for (auto Tile : FinalPath)
	{
		DrawDebugSphere(Grid->GetWorld(), Tile->Location + FVector::UpVector * 100.0f, 80.0f, 20, FColor::Black, false, 20.0f, 0, 8);

	}

	UE_LOG(LogTemp, Log, TEXT("Open list size: %d"), OpenList.Num())


	for (auto Tile : ClosedList)
	{
		DrawDebugSphere(Grid->GetWorld(), Tile.Cell->Location + FVector::UpVector * 100.0f, 80.0f, 20, FColor::Red, false, 20.0f, 0, 8);
	}*/

	
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
	FinalPath.Add(CellInfo->Cell);
	return BuildFinalPath(CellInfo->PreviousCell, FinalPath);
}

TArray<FGridCell*> AStar::FAStarPathFinder::BuildFinalPath(FTileInfo* CellInfo)
{
	TArray<FGridCell*> FinalPath;

	return BuildFinalPath(CellInfo, FinalPath);
}
