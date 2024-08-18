#include "T3DMapBuilderPlayerChessModeWidget.h"

#include "Utility/WidgetLayoutHelper.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

void ST3DMapBuilderPlayerChessModeWidget::Construct(const FArguments& InArgs)
{
	TSharedPtr<SVerticalBox> WidgetVerticalBox = SNew(SVerticalBox);

	SAssignNew(ModeSegmentedControl, SSegmentedControl<T3D::EMapBuilderPlayerPawnMode>)
		.Value(GBuilderWidgetContext.MapBuilderPlayerPawnMode.Get())
		.OnValueChanged_Lambda([this](T3D::EMapBuilderPlayerPawnMode NewMode)
		{
			GBuilderWidgetContext.MapBuilderPlayerPawnMode = NewMode;
		})
		+ SSegmentedControl<T3D::EMapBuilderPlayerPawnMode>::Slot(T3D::EMapBuilderPlayerPawnMode::Spawn)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("PlayerChessAddModeNameLabel", "Spawn PlayerChess"))
		+ SSegmentedControl<T3D::EMapBuilderPlayerPawnMode>::Slot(T3D::EMapBuilderPlayerPawnMode::Remove)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("PlayerChessRemoveModeNameLabel", "Remove PlayerChess"));

	T3D::NextVSlot(WidgetVerticalBox)
	[
		ModeSegmentedControl.ToSharedRef()
	];

	ChildSlot
	[
		WidgetVerticalBox.ToSharedRef()
	];
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION