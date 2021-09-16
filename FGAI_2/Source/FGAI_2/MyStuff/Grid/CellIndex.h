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
};
