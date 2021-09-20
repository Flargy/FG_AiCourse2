// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AStarSearchInterface.h"
#include "GameFramework/Actor.h"
#include "InterfaceTestActor.generated.h"

class APathingGrid;

UCLASS()
class FGAI_2_API AInterfaceTestActor : public AActor, public IAStarSearchInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInterfaceTestActor();

	UPROPERTY(EditAnywhere)
	APathingGrid* Grid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
