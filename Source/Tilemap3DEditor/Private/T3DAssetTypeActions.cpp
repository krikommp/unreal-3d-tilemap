#include "T3DAssetTypeActions.h"

#include "T3DEditorToolkit.h"

#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

FT3DAssetTypeActions::FT3DAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	:MyAssetCategory(InAssetCategory)
{
}

FText FT3DAssetTypeActions::GetName() const
{
	return LOCTEXT("FT3DAssetTypeActionsName", "3D Tilemap");
}

FColor FT3DAssetTypeActions::GetTypeColor() const
{
	return FColor(129, 196, 115);
}

UClass* FT3DAssetTypeActions::GetSupportedClass() const
{
	return UT3DAsset::StaticClass();
}

void FT3DAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EToolkitMode::Standalone;
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		const auto Asset = Cast<UT3DAsset>(*ObjIt);
		if (Asset != nullptr)
		{
			TSharedRef<FT3DEditorToolkit> NewToolkit(new FT3DEditorToolkit());
			NewToolkit->Initialize(Mode, EditWithinLevelEditor, Asset);
		}
	}
}

uint32 FT3DAssetTypeActions::GetCategories()
{
	return MyAssetCategory;
}

#undef LOCTEXT_NAMESPACE
