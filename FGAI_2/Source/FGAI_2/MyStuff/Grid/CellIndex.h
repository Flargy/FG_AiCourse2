#pragma once
#include "CellIndex.generated.h"

USTRUCT()
struct FCellIndex
{
	GENERATED_BODY()
	
public:

	FCellIndex(int R, int C)
	{
		Row = R;
		Column = C;
	};

	FCellIndex()
	{
		Row = 0;
		Column = 0;
	};
	
	int Row;

	int Column;

	FORCEINLINE bool operator==(const FCellIndex &Other) const
	{
		return Other.Column == Column && Other.Row == Row;
	}
};

struct FDirectionIndex{
	int Dx;
	int Dy;

	bool operator ==(FDirectionIndex const OtherIndex ) const
	{
		return OtherIndex.Dx == Dx && OtherIndex.Dy == Dy;
	}
}; 
