using UnrealBuildTool;

public class TracesOfLight : ModuleRules
{
	public TracesOfLight(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "RHI", "RenderCore" });
	}
}
