// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CC : ModuleRules
{
	public CC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Json", "JsonUtilities", "Niagara", "UMG",  "GameplayCameras" });

		PrivateDependencyModuleNames.AddRange(new string[] { "TraceInsights", "LevelSequence" });
		
		PublicIncludePaths.AddRange(new string[]
		{
			"CC/Public",
			"CC/Parser/Public",
			"CC/Parser/DataTableStruct/Public",
			"CC/GameMode/Public",
			"CC/FrameManager/Public",
			"CC/InputManager/Public",
			"CC/Utils/Public",
			"CC/FSM/Public/",
			"CC/FSM/CharacterStates/Public/",
			"CC/FSM/States/Public/",
			"CC/FSM/Conditions/Public/",
			"CC/FSM/SubFSM/Public/",
			"CC/TekkenAnimInstance/Public",
			"CC/DamageComponent/Public",
			"CC/Widget/Gauge/Public",
			"CC/Widget/Main/Public",
			"CC/Widget/HitLevel/Public",
			"CC/Widget/HitCombo/Public",
			"CC/Widget/KO/Public",
			"CC/Widget/ReadyFight/Public",
			"CC/CameraManager/Public",
			"CC/CameraManager/TekkenCameraShake/Public",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
