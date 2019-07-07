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
    UMAIBrainComponent();

    /** Ticking for heuristics. */
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


private:
    /** Exploration flag. */
    bool bShouldExplore = true;

    /** Closest box pointer. */
    AStaticMeshActor* Closest = nullptr;

    float deg = 0;
};
