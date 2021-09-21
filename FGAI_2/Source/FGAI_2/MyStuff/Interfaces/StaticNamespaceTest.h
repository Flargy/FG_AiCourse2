#pragma once

namespace AStar
{
	class FHeuristicCalculations
	{
	public:
		static void CallableFunction1()
		{
			UE_LOG(LogTemp, Warning, TEXT("Calling function 1"));
		}

		static int CallableFunction2()
		{
			return 2;
		}

		static void CallableFunction3();
	};



	
}