#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
//#include "Blackboard/BlackboardKeyType_TMap.h"
#include "MAIBlackboardComponent.generated.h"

UCLASS(ClassGroup = MAI, meta = (BlueprintSpawnableComponent))
class UMAIBlackboardComponent : public UBlackboardComponent
{
	GENERATED_BODY()

public:
    //template<typename keyname, typename keyvalue>
    /*void SetValueAsTMap(const FName& KeyName, TMap<APawn*, float> TMapValue)
    {
        const FBlackboard::FKey KeyID = GetKeyID(KeyName);
        SetValue<UBlackboardKeyType_TMap>(KeyID, TMapValue);
    }

    template<typename keyname, typename keyvalue>
    TMap<keyname, keyvalue> GetValueAsTMap(const FName& KeyName) const
    {
        return nullptr;//GetValue<UBlackboardKeyType_TMap>(KeyName);
    }*/
};
