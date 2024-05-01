// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Trajectory : ModuleRules
{
	public Trajectory(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "AnimGraphRuntime",
                "PoseSearch"
            }
        );
    }
}
