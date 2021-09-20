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

	FCellIndex(){};
	
	int Row;

	int Column;

	FORCEINLINE bool operator==(const FCellIndex &Other) const
	{
		return Other.Column == Column && Other.Row == Row;
	}
};
