// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheCore_IA : ModuleRules
{
	public TheCore_IA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = true;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AIModule", "GameplayTasks" });
	}
}
