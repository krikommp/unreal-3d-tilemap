#include "T3DMapBuilderWidget.h"

#include "MapBuilder/T3DMapBuilderModeWidget.h"
#include "Utility/WidgetLayoutHelper.h"
#include "MapBuilderModes/T3DMapBuilderBlockModeWidget.h"
#include "MapBuilderModes/T3DMapBuilderMeshModeWidget.h"
#include "MapBuilderModes/T3DMapBuilderPlayerChessModeWidget.h"
#include "MapBuilderModes/T3DMapBuilderPlayerStartModeWidget.h"
#include "MapBuilderModes/T3DMapBuilderViewModeWidget.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

void ST3DMapBuilderWidget::Construct(const FArguments& InArgs, TWeakObjectPtr<UT3DAsset> InAsset)
{
	T3DAsset = InAsset;

	TSharedPtr<SVerticalBox> WidgetVerticalBox = SNew(SVerticalBox);
	T3D::TitleSlot(WidgetVerticalBox, LOCTEXT("MapBuilderNameLabel", "MapBuilder"), VAlign_Center);
	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(ST3DMapBuilderModeWidget)
	];
	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(SBorder)
		.Visibility_Lambda([this]() { return GBuilderWidgetContext.MapBuilderMode.Get() == T3D::EMapBuilderMode::View ? EVisibility::Visible : EVisibility::Collapsed; })
		[
			SNew(ST3DMapBuilderViewModeWidget)
		]
	];
	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(SBorder)
		.Visibility_Lambda([this]() { return GBuilderWidgetContext.MapBuilderMode.Get() == T3D::EMapBuilderMode::Block ? EVisibility::Visible : EVisibility::Collapsed; })
		[
			SNew(ST3DMapBuilderBlockModeWidget, T3DAsset)
		]
	];
	T3D::NextVSlot(WidgetVerticalBox)
    [
        SNew(SBorder)
        .Visibility_Lambda([this]() { return GBuilderWidgetContext.MapBuilderMode.Get() == T3D::EMapBuilderMode::PlayerStart ? EVisibility::Visible : EVisibility::Collapsed; })
        [
            SNew(ST3DMapBuilderPlayerStartModeWidget)
        ]
    ];
	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(SBorder)
		.Visibility_Lambda([this]() { return GBuilderWidgetContext.MapBuilderMode.Get() == T3D::EMapBuilderMode::PlayerPawn ? EVisibility::Visible : EVisibility::Collapsed; })
		[
			SNew(ST3DMapBuilderPlayerChessModeWidget)
		]
	];
	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(SBorder)
		.Visibility_Lambda([this]() { return GBuilderWidgetContext.MapBuilderMode.Get() == T3D::EMapBuilderMode::Mesh ? EVisibility::Visible : EVisibility::Collapsed; })
		[
			SNew(ST3DMapBuilderMeshModeWidget, T3DAsset)
		]
	];

	ChildSlot
	[
		WidgetVerticalBox.ToSharedRef()
	];
}

#undef LOCTEXT_NAMESPACE
