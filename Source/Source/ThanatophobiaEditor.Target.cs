// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ThanatophobiaEditorTarget : TargetRules
{
	public ThanatophobiaEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("Thanatophobia");
		ExtraModuleNames.AddRange(new string[] { "ThanatophobiaToolsEditor", "ThanatophobiaTools" });
	}
}
