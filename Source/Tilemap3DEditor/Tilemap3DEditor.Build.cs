using UnrealBuildTool;

public class Tilemap3DEditor : ModuleRules
{
    public Tilemap3DEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        bPrecompile = true;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnableUndefinedIdentifierWarnings = false;
        PrivatePCHHeaderFile = "Private/Tilemap3DEditorPrivatePCH.h";
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "ToolMenus",
                "Tilemap3D", 
                "AdvancedPreviewScene", 
                "KismetWidgets",
                "ProceduralMeshComponent",
                "InputCore",
            }
        );
    }
}