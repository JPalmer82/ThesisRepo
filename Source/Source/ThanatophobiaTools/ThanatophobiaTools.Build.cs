using UnrealBuildTool;
	 
public class ThanatophobiaTools: ModuleRules
{
    public ThanatophobiaTools(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"});
    }
}