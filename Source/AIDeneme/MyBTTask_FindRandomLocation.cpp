// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UMyBTTask_FindRandomLocation::UMyBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location in NavMesh";
}

EBTNodeResult::Type UMyBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get AI controller and its npc
	if (auto* const cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const npc = cont->GetPawn())
		{
			// obtain NPC location
			auto const Origin = npc->GetActorLocation();

			// get the navigation system and generate a random location
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);

				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
