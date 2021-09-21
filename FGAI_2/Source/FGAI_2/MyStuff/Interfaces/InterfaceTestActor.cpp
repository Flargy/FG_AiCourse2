// Fill out your copyright notice in the Description page of Project Settings.

#include "InterfaceTestActor.h"
#include "StaticNamespaceTest.h"
#include "FGAI_2/MyStuff/Grid/PathingGrid.h"

using namespace AStar;

// Sets default values
AInterfaceTestActor::AInterfaceTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInterfaceTestActor::BeginPlay()
{
	Super::BeginPlay();

	Test = new TestHeuristics();
	
	if(Grid)
	{
		int Value = Grid->TestFunctionToCall(Test);
		
		UE_LOG(LogTemp, Warning, TEXT("Test function returned: %d"), Value)
		
		Grid->TestStaticCall(FHeuristicCalculations::CallableFunction1);
	}

	FHeuristicCalculations::CallableFunction1();
	
	UE_LOG(LogTemp, Warning, TEXT("Calling function %d"), FHeuristicCalculations::CallableFunction2());
	
	FHeuristicCalculations::CallableFunction3();

}

// Called every frame
void AInterfaceTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInterfaceTestActor::Destroyed()
{
	delete Test;
	Super::Destroyed();
}

