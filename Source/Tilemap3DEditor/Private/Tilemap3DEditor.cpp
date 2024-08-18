#include "Tilemap3DEditor.h"

#include "T3DAssetTypeActions.h"
#include "T3DEditorSettings.h"

#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE
DEFINE_LOG_CATEGORY(LogTilemap3DEditor);

void FTilemap3DEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	const EAssetTypeCategories::Type AssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Tilemap3D")), FText::FromName(TEXT("Tilemap3D")));
	T3DAssetTypeActions = MakeShared<FT3DAssetTypeActions>(AssetCategory);
	AssetTools.RegisterAssetTypeActions(T3DAssetTypeActions.ToSharedRef());

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	SettingsModule->RegisterSettings("Project", "Project", "TilemapEditor",
			LOCTEXT("Tilemap3DSettingsName", "Tilemap3D Editor"),
			LOCTEXT("Tilemap3DSettingsDesc", "Setting for tilemap3d"),
			GetMutableDefault<UT3DEditorSettings>());
}

void FTilemap3DEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::Get().GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(T3DAssetTypeActions.ToSharedRef());
	}

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Project", "TilemapEditor3D");
	}
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FTilemap3DEditorModule, Tilemap3DEditor)