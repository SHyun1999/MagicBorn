// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MagicBorn : ModuleRules
{
	public MagicBorn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayAbilities", "GameplayTags", "AIModule" });
	}
}
