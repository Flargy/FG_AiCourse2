#include "PathingGrid.h"
#include "Components/StaticMeshComponent.h"
#include "FGAI_2/Grid/FGGridBlockComponent.h"
#include "FGAI_2/MyStuff/Interfaces/HeuristicInterface.h"
#include "StaticMeshDescription.h"


APathingGrid::APathingGrid()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCastShadow(false);

	BlockStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockStaticMeshComponent"));
	BlockStaticMeshComponent->SetupAttachment(RootComponent);
	BlockStaticMeshComponent->SetCastShadow(false);
}

void APathingGrid::BeginPlay()
{
	Super::BeginPlay();

	if (AllCells.Num() == 0)
	{
		/*
		* If TileList is empty it probably means we just placed one in the level, so let's initialize it.
		*/

		AllCells.SetNum(GetNumTiles());
	}

	BuildGrid();

	UpdateBlockingTiles();
	DrawBlocks();
}

void APathingGrid::Tick(float DeltaSeconds)
{
}

void APathingGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	/*if (AllCells.Num() == 0)
	{
		

		AllCells.SetNum(GetNumTiles());
	}

	BuildGrid();

	UpdateBlockingTiles();
	DrawBlocks();*/
}


int32 APathingGrid::GetTileIndexFromXY(int32 TileX, int32 TileY) const
{
	if (TileX < 0 || TileX >= Rows)
		return false;

	if (TileY < 0 || TileY >= Columns)
		return false;

	const int32 TileIndex = (TileY * Rows) + TileX;
	

	if (!IsTileIndexValid(TileIndex))
		return 0;

	return TileIndex;
}

bool APathingGrid::IsTileIndexValid(int32 TileIndex) const
{
	const int32 NumTiles = AllCells.Num();

	if (TileIndex < 0 || TileIndex >= NumTiles)
	{
		return false;
	}

	return true;
}

FVector APathingGrid::GetWorldLocationFromXY(int32 TileX, int32 TileY) const
{
	const float X = ((static_cast<float>(TileX) - GetHalfWidth()) * TileSize) + GetTileSizeHalf();
	const float Y = ((static_cast<float>(TileY) - GetHalfHeight()) * TileSize) + GetTileSizeHalf();

	return GetActorTransform().TransformPosition(FVector(X, Y, 0));
}

bool APathingGrid::GetXYFromWorldLocation(const FVector& WorldLocation, int32& TileX, int32& TileY) const
{
	if (!IsWorldLocationInsideGrid(WorldLocation))
		return false;

	const FVector RelativeGridLocation = GetActorTransform().InverseTransformPositionNoScale(WorldLocation);

	const float HeightOffset = (Columns % 2) == 1 ? 0.5f : 0.0f;
	const float WidthOffset = (Rows % 2) == 1 ? 0.5f : 0.0f;

	const float X = FMath::FloorToInt(WidthOffset + (RelativeGridLocation.X / TileSize)) + GetHalfWidth() - WidthOffset;
	const float Y = FMath::FloorToInt(HeightOffset + (RelativeGridLocation.Y / TileSize)) + GetHalfHeight() - HeightOffset;

	TileX = FMath::Clamp(static_cast<int32>(X), 0, Columns - 1);
	TileY = FMath::Clamp(static_cast<int32>(Y), 0, Rows - 1);

	return true;
}

int32 APathingGrid::GetTileIndexFromWorldLocation(const FVector& WorldLocation) const
{
	int32 X = 0, Y = 0;
	if (GetXYFromWorldLocation(WorldLocation, X, Y))
	{
		return GetTileIndexFromXY(X, Y);
	}

	return 0;
}

FGridCell* APathingGrid::GetCellFromLocation(const FVector& WorldLocation)
{
	int32 X = 0, Y = 0;
	GetXYFromWorldLocation(WorldLocation, X, Y);
	
	//UE_LOG(LogTemp, Log, TEXT("Location: X:%f Y:%f"),AllCells[GetTileIndexFromXY(X, Y)].Location.X, AllCells[GetTileIndexFromXY(X, Y)].Location.Y)

	return &AllCells[GetTileIndexFromXY(Y, X)]; // reversed cause I was thinking rows to columns when the function uses columns to rows
	
	
}

FGridCell* APathingGrid::GetCellFromIndex(FCellIndex Index)
{
	return &AllCells[Index.Row * Rows + Index.Column];
}

bool APathingGrid::TransformWorldLocationToTileLocation(const FVector& InWorldLocation,
                                                        FVector& OutTileWorldLocation) const
{
	if (!IsWorldLocationInsideGrid(InWorldLocation))
		return false;

	int32 X = 0, Y = 0;
	if (GetXYFromWorldLocation(InWorldLocation, X, Y))
	{
		OutTileWorldLocation = GetWorldLocationFromXY(X, Y);
		return true;
	}

	return false;
}

bool APathingGrid::IsWorldLocationInsideGrid(const FVector& WorldLocation) const
{
	const FVector RelativeGridLocation = GetActorTransform().InverseTransformPositionNoScale(WorldLocation);

	if (RelativeGridLocation.X < -GetWidthSize())
		return false;
	else if (RelativeGridLocation.X > GetWidthSize())
		return false;
	else if (RelativeGridLocation.Y < -GetHeightSize())
		return false;
	else if (RelativeGridLocation.Y > GetHeightSize())
		return false;

	return true;
}

void APathingGrid::UpdateBlockingTiles()
{
	TArray<UFGGridBlockComponent*> AllBlocks;
	GetComponents(AllBlocks);

	//AllCells.Empty();
	//AllCells.SetNum(GetNumTiles());

	TArray<int32> BlockIndices;

	for (const auto Block : AllBlocks)
	{
		const FVector Origin = Block->GetComponentLocation();
		const FVector Extents = Block->Extents * 0.5f;

		BlockIndices.Reset();
		GetOverlappingTiles(Origin, Extents, BlockIndices);

		for (int32 Index = 0, Num = BlockIndices.Num(); Index < Num; ++Index)
		{
			AllCells[BlockIndices[Index]].bBlock = true;
			AllCells[BlockIndices[Index]].Type = Block->Type;
		}
	}

	DrawBlocks();
}

void APathingGrid::GetOverlappingTiles(const FVector& Origin, const FVector& Extent,
	TArray<int32>& OutOverlappingTiles) const
{
	const FBox BlockBox = FBox::BuildAABB(Origin, Extent);
	
	const FVector TileExtent(GetTileSizeHalf(), GetTileSizeHalf(), GetTileSizeHalf());

	FBox TileBox;

	for (int32 Y = Columns - 1; Y >= 0; --Y)
	{
		for (int32 X = 0; X < Rows; ++X)
		{
			const FVector TileWorldLocation = GetWorldLocationFromXY(X, Y);
			
			TileBox = FBox::BuildAABB(TileWorldLocation, TileExtent);
			if (TileBox.IntersectXY(BlockBox))
			{
				const int32 ArrayIndex = GetTileIndexFromXY(X, Y);
				OutOverlappingTiles.Add(ArrayIndex);
			}
		}
	}
}

#if WITH_EDITOR
void APathingGrid::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UpdateBlockingTiles();
}
#endif // WITH_EDITOR

void APathingGrid::BuildGrid()
{
	if (Rows < 1 || Columns < 1)
		return;
	
	const float Location_X = -(Rows * TileSize * 0.5f);
	const float Location_Y = -(Columns * TileSize * 0.5f);
	
#pragma region DrawBoxEdges
	if (MeshDescription == nullptr)
		MeshDescription = UStaticMesh::CreateStaticMeshDescription(this);

	if (GridMesh == nullptr)
		GridMesh = NewObject<UStaticMesh>(this, UStaticMesh::StaticClass());

	MeshDescription->Empty();

	FPolygonGroupID PGID = MeshDescription->CreatePolygonGroup();
	FPolygonID PID;

	

	for (int X = 0; X < Rows + 1; ++X)
	{
		float LocationOffset = X * TileSize;
		FVector Center = FVector(Location_X + LocationOffset, 0.0f, 0.0f);
		MeshDescription->CreateCube(Center, GetWidthExtends(), PGID, PID, PID, PID, PID, PID, PID);
	}

	for (int Y = 0; Y < Columns + 1; ++Y)
	{
		float LocationOffset = Y * TileSize;
		FVector Center = FVector(0.0f, Location_Y + LocationOffset, BorderSize);
		MeshDescription->CreateCube(Center, GetHeightExtends(), PGID, PID, PID, PID, PID, PID, PID);
	}

	TArray<UStaticMeshDescription*> MeshDescriptionList;
	MeshDescriptionList.Add(MeshDescription);
	GridMesh->BuildFromStaticMeshDescriptions(MeshDescriptionList);
	StaticMeshComponent->SetStaticMesh(GridMesh);
	
	

#pragma endregion

#pragma region CreateCells
	
	FVector ZeroPos = FVector(Location_X + TileSize * 0.5f, Location_Y + TileSize * 0.5f, GetActorLocation().Z);
	
	for(int r = 0; r < Rows; r++)
	{
		for (int c = 0; c < Columns; c++)
		{
			FVector CellOffset = FVector(TileSize * r, TileSize * c, 0.0f) + ZeroPos;
			AllCells[Rows * r + c].Location = CellOffset;
			UE_LOG(LogTemp, Log, TEXT("X: %f Y: %f"),CellOffset.X, CellOffset.Y)
		}
	}

#pragma endregion

	AssignNeighbors();
	
}

void APathingGrid::DrawBlocks()
{
	const int32 NumBlocks = AllCells.Num();

	if (NumBlocks == 0)
		return;

	if (BlockMeshDescription == nullptr)
		BlockMeshDescription = UStaticMesh::CreateStaticMeshDescription(this);

	if (BlockMesh == nullptr)
		BlockMesh = NewObject<UStaticMesh>(this, UStaticMesh::StaticClass());
		
	BlockMeshDescription->Empty();

	BlockStaticMeshComponent->SetStaticMesh(nullptr);

	FPolygonGroupID BlockPGID = BlockMeshDescription->CreatePolygonGroup();
	FPolygonID PID;

	const float BlockSize = TileSize * 0.25f;
	const FVector BlockExtent = FVector(BlockSize, BlockSize, BlockSize * 0.25f);

	for (int32 Y = Columns - 1; Y >= 0; --Y)
	{
		for (int32 X = 0; X < Rows; ++X)
		{
			const FVector TileRelativeLocation = GetActorTransform().InverseTransformPositionNoScale(GetWorldLocationFromXY(X, Y));
			const int32 ArrayIndex = GetTileIndexFromXY(X, Y);
			const ETileType Type = AllCells[ArrayIndex].Type;

			if (Type == Wall)
			{
				BlockMeshDescription->CreateCube(TileRelativeLocation, BlockExtent, BlockPGID, PID, PID, PID, PID, PID, PID);
			}
			if(Type == Water)
			{
				BlockMeshDescription->CreateCube(TileRelativeLocation, BlockExtent * 0.5f, BlockPGID, PID, PID, PID, PID, PID, PID);
			}
		}
	}

	if (!BlockMeshDescription->IsEmpty())
	{
		TArray<UStaticMeshDescription*> BlockMeshDescriptionList;
		BlockMeshDescriptionList.Add(BlockMeshDescription);
		BlockMesh->BuildFromStaticMeshDescriptions(BlockMeshDescriptionList);
		BlockStaticMeshComponent->SetStaticMesh(BlockMesh);
	}
}

void APathingGrid::AssignNeighbors()
{
	for(int r = 0; r < Rows; r++)
	{
		for (int c = 0; c < Columns; c++)
		{
			for(int i = 0; i < 8; i++)
			{
				int x = Directions[i].Dx;
				int y = Directions[i].Dy;

				if(r + x >= Rows || r + x < 0 || c + y >= Columns || c + y < 0)
				{
					continue;
				}
				const FCellIndex AdjacentCellIndex = FCellIndex(r + x,c + y);
				AllCells[Rows * r + c].SetNeighbor(AdjacentCellIndex);
				//UE_LOG(LogTemp, Log, TEXT("Me: %d:%d  Neighbor: %d:%d"),r,c,r + x, c + y)
			}
		}
	}
}
