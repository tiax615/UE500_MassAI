// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleRandomMovementProcessor.h"
#include "MassCommonTypes.h"
#include "SimpleRandomMovementFragment.h"
#include "MassCommonFragments.h"

USimpleRandomMovementProcessor::USimpleRandomMovementProcessor()
{
	// 自动注册，设置执行顺序
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)EProcessorExecutionFlags::All;
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void USimpleRandomMovementProcessor::ConfigureQueries()
{
	// 增加fragment需求
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite); // #include "MassCommonFragments.h"
	EntityQuery.AddRequirement<FSimpleRandomMovementFragment>(EMassFragmentAccess::ReadWrite);
}

void USimpleRandomMovementProcessor::Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntitySubsystem, Context, ([this](FMassExecutionContext& Context)
	{
		const TArrayView<FTransformFragment> TransformsList = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FSimpleRandomMovementFragment> SimpleMovementsList = Context.GetMutableFragmentView<FSimpleRandomMovementFragment>();
		const float WorldDeltaTime = Context.GetDeltaTimeSeconds();

		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			FTransform& Transform = TransformsList[EntityIndex].GetMutableTransform();
			FVector& MoveTarget = SimpleMovementsList[EntityIndex].Target;

			FVector CurrentLocation = Transform.GetLocation();
			FVector TargetVector = MoveTarget - CurrentLocation;

			if (TargetVector.Size() <= 20.f)
			{
				MoveTarget = FVector(FMath::RandRange(-1.f, 1.f) * 1000.f, FMath::RandRange(-1.f, 1.f) * 1000.f, CurrentLocation.Z);
			}
			else
			{
				Transform.SetLocation(CurrentLocation + TargetVector.GetSafeNormal() * 400.f * WorldDeltaTime);
			}
		}
	}));
}
