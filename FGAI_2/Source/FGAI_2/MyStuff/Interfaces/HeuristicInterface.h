#pragma once

#include "HeuristicInterface.generated.h"



UINTERFACE(MinimalAPI)
class UHeuristicInterface : public UInterface
{
	GENERATED_BODY()
};

class IHeuristicInterface
{
	GENERATED_BODY()
public:

	UFUNCTION()
	virtual	int TestFunctionPassing(int Value) = 0;
	
};