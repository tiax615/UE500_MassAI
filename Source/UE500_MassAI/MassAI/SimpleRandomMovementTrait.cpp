// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleRandomMovementTrait.h"
#include "SimpleRandomMovementFragment.h"
#include "MassEntityTemplateRegistry.h"

void USimpleRandomMovementTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	// 每个实体拥有状态数据，存下目标位置，数据是fragment
	BuildContext.AddFragment<FSimpleRandomMovementFragment>(); // #include "MassEntityTemplateRegistry.h"
}