// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HorrorGame : ModuleRules
{
	public HorrorGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HorrorGame",
			"HorrorGame/Variant_Platforming",
			"HorrorGame/Variant_Platforming/Animation",
			"HorrorGame/Variant_Combat",
			"HorrorGame/Variant_Combat/AI",
			"HorrorGame/Variant_Combat/Animation",
			"HorrorGame/Variant_Combat/Gameplay",
			"HorrorGame/Variant_Combat/Interfaces",
			"HorrorGame/Variant_Combat/UI",
			"HorrorGame/Variant_SideScrolling",
			"HorrorGame/Variant_SideScrolling/AI",
			"HorrorGame/Variant_SideScrolling/Gameplay",
			"HorrorGame/Variant_SideScrolling/Interfaces",
			"HorrorGame/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
