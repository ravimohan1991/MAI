// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

using UnrealBuildTool;
using System.IO;

public class MAI : ModuleRules
{
    public MAI(ReadOnlyTargetRules Target) : base(Target)
    {

	bFasterWithoutUnity = true;
        MinFilesUsingPrecompiledHeaderOverride = 1;
        PrivatePCHHeaderFile = "Public/MAI.h";
        PublicIncludePaths.AddRange(new string[] { 
            "MAI/Public"
        });
        PrivateIncludePaths.AddRange(new string[] {
            "MAI/Private"
        });

	PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule"});

    }
}
