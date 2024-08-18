#include "T3DMapBuilderBlockModeWidget.h"

#include "Engine/Texture2D.h"
#include "Utility/WidgetLayoutHelper.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

void ST3DSingleCubeBlockPreviewWidget::Construct(const FArguments& InArgs, const FT3DBlockConfig& InConfig)
{
	UTexture2D* PreviewTex = InConfig.BlockTextures.Num() > 1 ? InConfig.BlockTextures[1] : InConfig.BlockTextures[0];
	checkf(PreviewTex, TEXT("Can not get first texture，check config."));

	PreviewTexBrush = MakeShareable(new FSlateBrush);
	PreviewTexBrush->SetResourceObject(PreviewTex);
	PreviewTexBrush->SetImageSize(FVector2D(64, 64));
	PreviewTexBrush->DrawAs = ESlateBrushDrawType::Image;

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SImage)
			.Image(PreviewTexBrush.Get())
		]
		+ SVerticalBox::Slot()
		  .Padding(0.0f, 10.0f)
		  .AutoHeight()
		[
			SNew(SButton)
			.OnClicked_Lambda([=, this]()
			{
				// ReSharper disable once CppExpressionWithoutSideEffects
				GBuilderWidgetContext.SelectedCubeBlockID = InConfig.ID;
				return FReply::Handled();
			})
			[
				SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.Text(FText::FromName(InConfig.ID))
			]
		]
	];
}

void ST3DBlockPreviewWidget::Construct(const FArguments& InArgs, const TWeakObjectPtr<UT3DAsset>& InAsset)
{
	T3DAsset = InAsset;

	SAssignNew(TileCubeBlockBox, SHorizontalBox);

	for (const FT3DBlockConfig& BlockConfig : T3DAsset->TilemapConfig->BlockConfigs)
	{
		if (BlockConfig.BlockTextures.Num() <= 0)
			continue;
		TileCubeBlockBox->AddSlot()
		.AutoWidth()
		.Padding(10.0f)
		[
			SNew(ST3DSingleCubeBlockPreviewWidget, BlockConfig)
		];
	}

	ChildSlot
	[
		TileCubeBlockBox.ToSharedRef()
	];
}

void ST3DMapBuilderBlockModeWidget::Construct(const FArguments& InArgs, const TWeakObjectPtr<UT3DAsset>& InAsset)
{
	// /Script/Engine.MaterialInstanceConstant'/Tilemap3D/MAT_INS_T3D_Editor_Ground.MAT_INS_T3D_Editor_Ground'
	T3DAsset = InAsset;

	TSharedPtr<SVerticalBox> WidgetVerticalBox = SNew(SVerticalBox);

	SAssignNew(ModeSegmentedControl, SSegmentedControl<T3D::EMapBuilderBlockSubMode>)
		.Value(GBuilderWidgetContext.MapBuilderBlockSubMode.Get())
		.OnValueChanged_Lambda([this](T3D::EMapBuilderBlockSubMode NewMode)
		{
			GBuilderWidgetContext.MapBuilderBlockSubMode = NewMode;
		})
		+ SSegmentedControl<T3D::EMapBuilderBlockSubMode>::Slot(T3D::EMapBuilderBlockSubMode::Add)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("BlockAddModeNameLabel", "Add Block"))
		+ SSegmentedControl<T3D::EMapBuilderBlockSubMode>::Slot(T3D::EMapBuilderBlockSubMode::Remove)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("BlockRemoveModeNameLabel", "Remove Block"));

	T3D::NextVSlot(WidgetVerticalBox)
	[
		ModeSegmentedControl.ToSharedRef()
	];

	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(SBorder)
        .Visibility_Lambda([this]() { return GBuilderWidgetContext.MapBuilderBlockSubMode.Get() == T3D::EMapBuilderBlockSubMode::Add ? EVisibility::Visible : EVisibility::Collapsed; })
        [
        	SNew(ST3DBlockPreviewWidget, T3DAsset)
        ]
	];

	T3D::NextVSlot(WidgetVerticalBox, LOCTEXT("HalfBlockCheckLabel", "Half Block"))
	[
		SNew(SCheckBox)
		.IsChecked_Lambda([this]() { return GBuilderWidgetContext.bHalfBlock.Get() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
		.OnCheckStateChanged_Lambda([this](ECheckBoxState NewState)
		{
			GBuilderWidgetContext.bHalfBlock = NewState == ECheckBoxState::Checked;
		})
	];
	
	T3D::NextVSlot(WidgetVerticalBox, LOCTEXT("FillPaintCheckLabel", "Fill Paint"))
	[
		SNew(SCheckBox)
		.IsChecked_Lambda([this]() { return GBuilderWidgetContext.bFillPaint.Get() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
		.OnCheckStateChanged_Lambda([this](ECheckBoxState NewState)
		{
			GBuilderWidgetContext.bFillPaint = NewState == ECheckBoxState::Checked;
		})
	];

	ChildSlot
	[
		WidgetVerticalBox.ToSharedRef()
	];
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
