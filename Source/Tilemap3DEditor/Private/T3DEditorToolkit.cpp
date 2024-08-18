#include "T3DEditorToolkit.h"

#include "T3DEditorCommands.h"
#include "Generator/T3DTerrainGenerator.h"
#include "Widgets/T3DEditorSceneViewport.h"
#include "Widgets/T3DPropertiesTabBody.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

const FName FT3DEditorToolkit::ViewportID(TEXT("TilemapViewport"));
const FName FT3DEditorToolkit::DetailsID(TEXT("TilemapDetails"));

FT3DEditorToolkit::FT3DEditorToolkit()
{
}

void FT3DEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorldSpaceMenu_Tilemap3DEditor", "3D Tilemap Editor"));
	const auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(ViewportID, FOnSpawnTab::CreateSP(this, &FT3DEditorToolkit::SpawnTab_Viewport))
		.SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Viewports"));

	InTabManager->RegisterTabSpawner(DetailsID, FOnSpawnTab::CreateSP(this, &FT3DEditorToolkit::SpawnTab_Details))
		.SetDisplayName(LOCTEXT("DetailsTabLabel", "Details"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FT3DEditorToolkit::Initialize(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UT3DAsset* Asset)
{
	GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->CloseOtherEditors(Asset, this);
	TSharedRef<FT3DEditorToolkit> EditorToolkit = SharedThis(this);
	T3DAsset = Asset;

	Viewport = SNew(ST3DEditorSceneViewport, T3DAsset.Get());
	PropertiesTabBody = SNew(ST3DPropertiesTabBody, T3DAsset, EditorToolkit);

	GBuilderWidgetContext.Invoker = MakeUnique<FT3DInvoker>();

	BindCommand();

	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("TilemapAssetEditor_Layout")
	->AddArea(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewSplitter()
			->SetOrientation(Orient_Horizontal)
			->SetSizeCoefficient(0.9f)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.8f)
				->SetHideTabWell(true)
				->AddTab(ViewportID, ETabState::OpenedTab)
			)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->AddTab(DetailsID, ETabState::OpenedTab)
			)
		)
	);

	constexpr bool bCreateDefaultStandaloneMenu = true;
	constexpr bool bCreateDefaultToolbar = true;
	const FName AppIdentifier = TEXT("Tilemap3DAssetEditor");
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, AppIdentifier, Layout, bCreateDefaultStandaloneMenu,
										 bCreateDefaultToolbar, Asset);
}

void FT3DEditorToolkit::BindCommand()
{
	FT3DEditorCommands::Register();
	const FT3DEditorCommands& Commands = FT3DEditorCommands::Get();

	ToolkitCommands->MapAction(
		Commands.UndoBuilderCommand,
		FExecuteAction::CreateSP(this, &FT3DEditorToolkit::OnUndoBuilderInvoked),
		FCanExecuteAction::CreateLambda([](){ return true; }));
}

void FT3DEditorToolkit::OnUndoBuilderInvoked()
{
	GBuilderWidgetContext.Invoker->UndoLastCommand();
}

void FT3DEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(DetailsID);
	InTabManager->UnregisterTabSpawner(ViewportID);
}

FName FT3DEditorToolkit::GetToolkitFName() const
{
	return FName("Tilemap3DAsset");
}

FText FT3DEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("Tilemap3DAssetLabel", "Tilemap3DAsset");
}

FString FT3DEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("Tilemap3DAssetTabPrefix", "Tilemap3DAsset").ToString();
}

FLinearColor FT3DEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

void FT3DEditorToolkit::AddReferencedObjects(FReferenceCollector& Collector)
{
}

FString FT3DEditorToolkit::GetReferencerName() const
{
	return TEXT("FTilemap3DEditorToolkit");
}

TSharedRef<SDockTab> FT3DEditorToolkit::SpawnTab_Viewport(const FSpawnTabArgs& Args) const
{
	return SNew(SDockTab)
	.TabRole(ETabRole::NomadTab)
	[
		Viewport.ToSharedRef()
	];
}

TSharedRef<SDockTab> FT3DEditorToolkit::SpawnTab_Details(const FSpawnTabArgs& Args) const
{
	return SNew(SDockTab)
	.Label(LOCTEXT("TilemapDetailsTitle", "Details"))
	[
		PropertiesTabBody.ToSharedRef()
	];
}

#undef LOCTEXT_NAMESPACE
