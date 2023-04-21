// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MassAI : ModuleRules
{
	public MassAI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				// AI/MassAI Plugin Modules
				"MassAIBehavior",
				"MassAIDebug",
				"MassNavigation",
				"MassZoneGraphNavigation",
				
				// AI/MassCrowd Plugin Modules
				"MassCrowd",

				// Runtime/MassEntity Plugin Modules
				"MassEntity",

				// Runtime/MassGameplay Plugin Modules
				"MassActors",
				"MassCommon",
				"MassGameplayDebug",
				"MassLOD",
				"MassMovement",
				"MassReplication",
				"MassRepresentation",
				"MassSignals",
				"MassSimulation",
				"MassSmartObjects",
				"MassSpawner",
				
				"SmartObjectsModule", // work around until we find a better way to get data from smart object configs
				
				// Misc
				"AnimToTexture",
				"ContextualAnimation",
				"Core",
				"Engine",
				"MotionWarping",
				"DeveloperSettings",
				"StateTreeModule",
				"StructUtils",
				"ZoneGraph",
				"ZoneGraphDebug",
				// "MassTraffic",
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Slate",
				"SlateCore",
				"GameplayTasks",
				"MassSimulation",
				"RenderCore",
				"RHI"
			}
		);

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
