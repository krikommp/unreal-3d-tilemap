#include "T3DMapBuilderModeWidget.h"

#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

void ST3DMapBuilderModeWidget::Construct(const FArguments& InArgs)
{
	SAssignNew(ModeSegmentedControl, SSegmentedControl<T3D::EMapBuilderMode>)
		.Value(GBuilderWidgetContext.MapBuilderMode.Get())
		.OnValueChanged_Lambda([this](T3D::EMapBuilderMode NewMode) { GBuilderWidgetContext.MapBuilderMode = NewMode; })
		+ SSegmentedControl<T3D::EMapBuilderMode>::Slot(T3D::EMapBuilderMode::View)
		  .Icon(FAppStyle::Get().GetBrush("LandscapeEditor.SelectComponentTool"))
		  .Text(LOCTEXT("ViewMenuModeNameLabel", "View Mode"))
		+ SSegmentedControl<T3D::EMapBuilderMode>::Slot(T3D::EMapBuilderMode::Block)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("BlockMenuModeNameLabel", "Block Mode"))
		+ SSegmentedControl<T3D::EMapBuilderMode>::Slot(T3D::EMapBuilderMode::Mesh)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("MeshMenuModeNameLabel", "Mesh Mode"))
		+ SSegmentedControl<T3D::EMapBuilderMode>::Slot(T3D::EMapBuilderMode::AIPawn)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("AIPawnMenuModeNameLabel", "AIPawn Mode"))
		+ SSegmentedControl<T3D::EMapBuilderMode>::Slot(T3D::EMapBuilderMode::PlayerPawn)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("PawnMenuModeNameLabel", "Pawn Mode"))
		+ SSegmentedControl<T3D::EMapBuilderMode>::Slot(T3D::EMapBuilderMode::PlayerStart)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("PlayerStartMenuModeNameLabel", "Player Start Mode"));

	ChildSlot
	[
		ModeSegmentedControl.ToSharedRef()
	];
}
#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
