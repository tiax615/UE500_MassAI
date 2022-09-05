// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "SimpleRandomMovementFragment.generated.h"

USTRUCT()
struct FSimpleRandomMovementFragment : public FMassFragment
{
	GENERATED_BODY()
	FVector Target;
};