#pragma once

#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BlackboardKeyType_TMap.generated.h"

UCLASS()
class UBlackboardKeyType_TMap : public UBlackboardKeyType
{
    GENERATED_BODY()

   /* typedef TMap<APawn*, float> FDataType;
    static const FDataType InvalidValue;

    template<typename keyname, typename keyvalue>
    static TMap<keyname, keyvalue> GetValue(const UBlackboardKeyType_TMap* KeyObj, const uint8* RawData);

   // template<typename keyname, typename keyvalue>
    bool SetValue(const UBlackboardKeyType_TMap* KeyObj, const uint8* RawData, TMap<APawn*, float> Value);
*/
};
