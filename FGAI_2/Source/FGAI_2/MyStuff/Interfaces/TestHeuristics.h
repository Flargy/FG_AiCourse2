#pragma once
#include "HeuristicInterface.h"

class TestHeuristics :  public IHeuristicInterface
{
	
public:

	virtual int TestFunctionPassing(int Value) override;
};
