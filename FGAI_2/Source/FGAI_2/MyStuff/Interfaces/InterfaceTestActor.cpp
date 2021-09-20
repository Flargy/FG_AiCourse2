// Fill out your copyright notice in the Description page of Project Settings.


#include "InterfaceTestActor.h"

#include "FGAI_2/MyStuff/Grid/PathingGrid.h"


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
	
	if(Grid)
	{
		int Test = Grid->TestFunctionToCall(TestFunctionPassing);
		UE_LOG(LogTemp, Log, TEXT("Value was received: %d"),Test)
	}
}

// Called every frame
void AInterfaceTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

