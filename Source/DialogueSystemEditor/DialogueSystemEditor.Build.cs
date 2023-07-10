using UnrealBuildTool;

public class DialogueSystemEditor : ModuleRules
{
    public DialogueSystemEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "AssetTools", "DialogueSystem"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "DialogueSystem",
                "UnrealEd",
                "EditorStyle",
                "Projects",
            }
        );
    }
}