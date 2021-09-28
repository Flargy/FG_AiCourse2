#pragma once
#include "CellIndex.generated.h"

struct FDirectionIndex{
	int Dx;
	int Dy;

	bool operator ==(FDirectionIndex const OtherIndex ) const
	{
		return OtherIndex.Dx == Dx && OtherIndex.Dy == Dy;
	}
};

USTRUCT()
struct FCellIndex
{
	GENERATED_BODY()
	
public:

	FCellIndex(int R, int C, FDirectionIndex DirectionIndex)
	{
		Row = R;
		Column = C;
		Direction = DirectionIndex;
	};

	FCellIndex(int R, int C)
	{
		Row = R;
		Column = C;
		Direction = {0,0};
	};

	FCellIndex()
	{
		Row = 0;
		Column = 0;
		Direction = {0,0};

	};
	
	int Row;

	int Column;

	FDirectionIndex Direction;

	FORCEINLINE bool operator==(const FCellIndex &Other) const
	{
		return Other.Column == Column && Other.Row == Row;
	}
};

 
