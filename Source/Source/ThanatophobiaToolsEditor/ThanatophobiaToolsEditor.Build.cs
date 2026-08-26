using UnrealBuildTool;
	 
public class ThanatophobiaToolsEditor: ModuleRules
{
    public ThanatophobiaToolsEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "ThanatophobiaTools", "Slate", "SlateCore", "UnrealEd"});
    }
}