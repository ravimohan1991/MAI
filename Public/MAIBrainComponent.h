// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#pragma once

#include "Runtime/AIModule/Classes/BrainComponent.h"
#include "MAIController.h"
#include "MAIBrainComponent.generated.h"

UCLASS()
class UMAIBrainComponent : public UBrainComponent
{
    GENERATED_BODY()

public:

    //UMAIBrainComponent( AMAIController* ACont = nullptr );

    /** Setting the owner.*/
    void SetOwner( AAIController* ACont ){AIOwner = ACont;}

};
