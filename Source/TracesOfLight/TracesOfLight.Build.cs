using UnrealBuildTool;

public class TracesOfLight : ModuleRules
{
	public TracesOfLight(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
