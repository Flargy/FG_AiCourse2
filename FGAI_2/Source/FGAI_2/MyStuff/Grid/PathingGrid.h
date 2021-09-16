#pragma once

#include "GameFramework/Actor.h"
#include "GridCell.h"
#include "PathingGrid.generated.h"

USTRUCT(BlueprintType)
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
};

class UStaticMeshComponent;
class UStaticMesh;
class UStaticMeshDescription;

UCLASS()
class APathingGrid : public AActor
{
	GENERATED_BODY()

public:
	
#pragma region UnrealSpecificFunctions
	
	APathingGrid();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;

#pragma endregion
	
#pragma region Variables
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY()
	UStaticMeshComponent* BlockStaticMeshComponent = nullptr;

	UPROPERTY()
	UStaticMesh* GridMesh = nullptr;

	UPROPERTY()
	UStaticMesh* BlockMesh = nullptr;

	UPROPERTY()
	UStaticMeshDescription* MeshDescription = nullptr;

	UPROPERTY()
	UStaticMeshDescription* BlockMeshDescription = nullptr;
	
	UPROPERTY(EditInstanceOnly)
	int Rows = 5;

	UPROPERTY(EditInstanceOnly)
	int Columns = 5;

	UPROPERTY(EditInstanceOnly)
	int CellMargin = 5;

	UPROPERTY(EditInstanceOnly)
	float BaseMovementCost = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grid)
	float TileSize = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grid, meta = (ClampMin = 0.1))
	float BorderSize = 10.0f;

#pragma endregion

#pragma region Functions

	TArray<FGridCell> GeneratePath(FVector StartingLocation, FVector EndLocation); // add agent type to this later

	FGridCell GetCellFromVector(FVector Location);

	FGridCell GetCellFromIndex(FCellIndex Index);

	UFUNCTION(BlueprintPure, Category = "Grid")
    float GetTileSizeHalf() const { return TileSize * 0.5f; }
	UFUNCTION(BlueprintPure, Category = "Grid")
    int32 GetNumTiles() const { return Rows * Columns; }
	UFUNCTION(BlueprintPure, Category = "Grid")
    float GetGridSize() const { return GetNumTiles() * TileSize; }

	UFUNCTION(BlueprintPure, Category = "Grid")
    float GetHalfWidth() const { return static_cast<float>(Rows) * 0.5f; }
	UFUNCTION(BlueprintPure, Category = "Grid")
    float GetHalfHeight() const { return static_cast<float>(Columns) * 0.5f; }

	UFUNCTION(BlueprintPure, Category = "Grid")
    float GetWidthSize() const { return (static_cast<float>(Rows) * GetTileSizeHalf()) + BorderSize; }
	UFUNCTION(BlueprintPure, Category = "Grid")
    float GetHeightSize() const { return (static_cast<float>(Columns) * GetTileSizeHalf()) + BorderSize; }

	UFUNCTION(BlueprintPure, Category = "Grid")
    FVector GetWidthExtends() const { return FVector(BorderSize, GetHeightSize(), BorderSize); }
	UFUNCTION(BlueprintPure, Category = "Grid")
    FVector GetHeightExtends() const { return FVector(GetWidthSize(), BorderSize, BorderSize); }

	UFUNCTION(BlueprintPure, Category = "Grid")
    int32 GetTileIndexFromXY(int32 TileX, int32 TileY) const;
	bool IsTileIndexValid(int32 TileIndex) const;

	UFUNCTION(BlueprintPure, Category = "Grid")
    FVector GetWorldLocationFromXY(int32 TileX, int32 TileY) const;

	UFUNCTION(BlueprintPure, Category = "Grid")
    bool GetXYFromWorldLocation(const FVector& WorldLocation, int32& TileX, int32& TileY) const;

	UFUNCTION(BlueprintPure, Category = "Grid")
    int32 GetTileIndexFromWorldLocation(const FVector& WorldLocation) const;

	UFUNCTION(BlueprintPure, Category = "Grid")
    bool TransformWorldLocationToTileLocation(const FVector& InWorldLocation, FVector& OutTileWorldLocation) const;

	bool IsWorldLocationInsideGrid(const FVector& WorldLocation) const;
	
	void UpdateBlockingTiles();

	void GetOverlappingTiles(const FVector& Origin, const FVector& Extent, TArray<int32>& OutOverlappingTiles) const;

	
#if WITH_EDITOR
	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR
	
#pragma endregion

private:

#pragma region Variables

	UPROPERTY(Transient)
	TArray<FGridCell> AllCells;


	
#pragma endregion 

#pragma region Functions

	void BuildGrid();

	void DrawBlocks();
	
	void AssignNeighbors(int Row, int Column);
	
#pragma endregion 
};