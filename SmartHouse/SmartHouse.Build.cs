// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SmartHouse : ModuleRules
{
	public SmartHouse(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG",
            "Slate", "SlateCore" });
	}
}
