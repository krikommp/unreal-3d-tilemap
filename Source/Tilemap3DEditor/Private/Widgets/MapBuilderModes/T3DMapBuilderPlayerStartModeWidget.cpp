#include "T3DMapBuilderPlayerStartModeWidget.h"

#include "Utility/WidgetLayoutHelper.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

void ST3DMapBuilderPlayerStartModeWidget::Construct(const FArguments& InArgs)
{
	TSharedPtr<SVerticalBox> WidgetVerticalBox = SNew(SVerticalBox);

	SAssignNew(ModeSegmentedControl, SSegmentedControl<T3D::EMapBuilderPlayerStartMode>)
		.Value(GBuilderWidgetContext.MapBuilderPlayerStartMode.Get())
		.OnValueChanged_Lambda([this](T3D::EMapBuilderPlayerStartMode NewMode)
		{
			GBuilderWidgetContext.MapBuilderPlayerStartMode = NewMode;
		})
		+ SSegmentedControl<T3D::EMapBuilderPlayerStartMode>::Slot(T3D::EMapBuilderPlayerStartMode::Spawn)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("PlayerStartAddModeNameLabel", "Spawn PlayerStart"))
		+ SSegmentedControl<T3D::EMapBuilderPlayerStartMode>::Slot(T3D::EMapBuilderPlayerStartMode::Remove)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("PlayerStartRemoveModeNameLabel", "Remove PlayerStart"));

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