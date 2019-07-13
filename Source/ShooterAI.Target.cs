// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;

public class ShooterAITarget : TargetRules
{
	public ShooterAITarget(TargetInfo Target) : base(Target)
	{
		//Type = TargetType.Game;
		ExtraModuleNames.Add("ShooterAI");
		//ExtraModuleNames.Add("MAI");
		// ExtraModuleNames.AddRange(new string[]{
		//"ShooterAI",
		//"MAI"		
		//});		
	}
}
