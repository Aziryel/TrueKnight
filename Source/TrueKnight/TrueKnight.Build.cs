// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TrueKnight : ModuleRules
{
	public TrueKnight(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayAbilities", 
			"Paper2D", 
			"CommonUI",
			"UMG",
			"Slate",
			"SlateCore", "PaperZD"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks", "Niagara", "AIModule" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
