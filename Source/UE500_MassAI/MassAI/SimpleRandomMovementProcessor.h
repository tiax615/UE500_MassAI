// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "SimpleRandomMovementProcessor.generated.h"

UCLASS()
class UE500_MASSAI_API USimpleRandomMovementProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:
	USimpleRandomMovementProcessor();

protected:
	virtual void ConfigureQueries() override; // 增加fragment需求
	virtual void Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context) override;

private:
	FMassEntityQuery EntityQuery; // 处理数据
};
