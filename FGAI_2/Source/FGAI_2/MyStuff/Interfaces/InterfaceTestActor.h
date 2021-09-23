// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestHeuristics.h"
#include "InterfaceTestActor.generated.h"

class APathingGrid;

UCLASS()
class FGAI_2_API AInterfaceTestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInterfaceTestActor();

	UPROPERTY(EditAnywhere)
	APathingGrid* Grid;

	UPROPERTY(EditInstanceOnly)
	AActor* GoalPoint;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

	//TestHeuristics* Test; // this or the other version
	//TestHeuristics Test;
};
