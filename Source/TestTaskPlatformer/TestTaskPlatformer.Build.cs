// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestTaskPlatformer : ModuleRules
{
	public TestTaskPlatformer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(new string[]
        {
            //"TestTaskPlatformer/Public/Player"
            //"TestTaskPlatformer/Public/Components",
            //"TestTaskPlatformer/Public/UI",
            //"TestTaskPlatformer/Public/Animations",
            //"TestTaskPlatformer/Public/Menu",
            //"TestTaskPlatformer/Public/Menu/UI"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}