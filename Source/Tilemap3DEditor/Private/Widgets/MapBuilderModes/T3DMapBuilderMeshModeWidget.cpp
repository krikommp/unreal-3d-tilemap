#include "T3DMapBuilderMeshModeWidget.h"

#include "Command/T3DCommands.h"
#include "Engine/Texture2D.h"
#include "Utility/MapBuildHelper.h"
#include "Utility/WidgetLayoutHelper.h"
#include "Widgets/Input/SRotatorInputBox.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

#define GET_SELECTED_MESH_BLOCK_SCALE(Axis) \
	if (InAsset->Block.IsValidIndex(GBuilderWidgetContext.SelectedMeshBlockIndex.Get())) \
	{\
	return (float)InAsset->Block[GBuilderWidgetContext.SelectedMeshBlockIndex.Get()].MeshLoc.Scale.Axis; \
	}\
	return 1.0f

#define GET_SELECTED_MESH_BLOCK_ROTATOR(Axis) \
	if (InAsset->Block.IsValidIndex(GBuilderWidgetContext.SelectedMeshBlockIndex.Get())) \
	{ \
		return (float)InAsset->Block[GBuilderWidgetContext.SelectedMeshBlockIndex.Get()].MeshLoc.Rotation.Axis; \
	} \
	return 1.0f;

void ST3DMeshActorPreviewWidget::Construct(const FArguments& InArgs, const TWeakObjectPtr<UT3DAsset>& InAsset)
{
	TSharedPtr<SVerticalBox> WidgetVerticalBox = SNew(SVerticalBox);
	
	T3D::NextVSlot(WidgetVerticalBox, LOCTEXT("MeshScaleSettingLabel", "Mesh Scale"))
	[
		SNew(SVectorInputBox)
		.X_Lambda([&InAsset]()
		{
			GET_SELECTED_MESH_BLOCK_SCALE(X);
		})
		.OnXCommitted_Lambda([&InAsset](float NewValue, ETextCommit::Type CommitType)
		{
			GBuilderWidgetContext.Invoker->Execute(new FT3DModifyMeshScaleX(InAsset, GBuilderWidgetContext.SelectedMeshBlockIndex.Get(), NewValue));
		})
		.Y_Lambda([&InAsset]()
		{
			GET_SELECTED_MESH_BLOCK_SCALE(Y);
		})
		.OnYCommitted_Lambda([&InAsset](float NewValue, ETextCommit::Type CommitType)
		{
			GBuilderWidgetContext.Invoker->Execute(new FT3DModifyMeshScaleY(InAsset, GBuilderWidgetContext.SelectedMeshBlockIndex.Get(), NewValue));
		})
		.Z_Lambda([&InAsset]()
		{
			GET_SELECTED_MESH_BLOCK_SCALE(Z);
		})
		.OnZCommitted_Lambda([&InAsset](float NewValue, ETextCommit::Type CommitType)
		{
			GBuilderWidgetContext.Invoker->Execute(new FT3DModifyMeshScaleZ(InAsset, GBuilderWidgetContext.SelectedMeshBlockIndex.Get(), NewValue));
		})
	];

	T3D::NextVSlot(WidgetVerticalBox, LOCTEXT("MeshRotatorSettingLabel", "Mesh Rotator"))
	[
		SNew(SRotatorInputBox)
		.Yaw_Lambda([&InAsset]()
		{
			GET_SELECTED_MESH_BLOCK_ROTATOR(Yaw);
		})
		.OnYawCommitted_Lambda([&InAsset](float NewValue, ETextCommit::Type CommitType)
		{
			GBuilderWidgetContext.Invoker->Execute(new FT3DModifyMeshRotatorYaw(InAsset, GBuilderWidgetContext.SelectedMeshBlockIndex.Get(), NewValue));
		})
		.Pitch_Lambda([&InAsset]()
		{
			GET_SELECTED_MESH_BLOCK_ROTATOR(Pitch);
		})
		.OnPitchCommitted_Lambda([&InAsset](float NewValue, ETextCommit::Type CommitType)
		{
			GBuilderWidgetContext.Invoker->Execute(new FT3DModifyMeshRotatorPitch(InAsset, GBuilderWidgetContext.SelectedMeshBlockIndex.Get(), NewValue));
		})
		.Roll_Lambda([&InAsset]()
		{
			GET_SELECTED_MESH_BLOCK_ROTATOR(Roll);
		})
		.OnRollCommitted_Lambda([&InAsset](float NewValue, ETextCommit::Type CommitType)
		{
			GBuilderWidgetContext.Invoker->Execute(new FT3DModifyMeshRotatorRoll(InAsset, GBuilderWidgetContext.SelectedMeshBlockIndex.Get(), NewValue));
		})
	];

	ChildSlot
	[
		WidgetVerticalBox.ToSharedRef()
	];
}

void ST3DSingleMeshPreviewWidget::Construct(const FArguments& InArgs, const FT3DMeshConfig& InConfig)
{
	UTexture2D* PreviewTex = T3D::GetThumbnailFromStaticMesh(InConfig.Mesh);

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
				GBuilderWidgetContext.SelectedMeshBlockID = InConfig.ID;
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

void ST3DMeshPreviewWidget::Construct(const FArguments& InArgs, const TWeakObjectPtr<UT3DAsset>& InAsset)
{
	T3DAsset = InAsset;

	SAssignNew(TileMeshBlockBox, SHorizontalBox);

	for (const FT3DMeshConfig& BlockConfig : T3DAsset->TilemapConfig->MeshConfigs)
	{
		TileMeshBlockBox->AddSlot()
		                .AutoWidth()
		                .Padding(10.0f)
		[
			SNew(ST3DSingleMeshPreviewWidget, BlockConfig)
		];
	}

	ChildSlot
	[
		TileMeshBlockBox.ToSharedRef()
	];
}

void ST3DMapBuilderMeshModeWidget::Construct(const FArguments& InArgs, const TWeakObjectPtr<UT3DAsset>& InAsset)
{
	T3DAsset = InAsset;

	TSharedPtr<SVerticalBox> WidgetVerticalBox = SNew(SVerticalBox);

	SAssignNew(ModeSegmentedControl, SSegmentedControl<T3D::EMapBuilderMeshSubMode>)
		.Value(GBuilderWidgetContext.MapBuilderMeshSubMode.Get())
		.OnValueChanged_Lambda([this](T3D::EMapBuilderMeshSubMode NewMode)
		{
			GBuilderWidgetContext.MapBuilderMeshSubMode = NewMode;
		})
		+ SSegmentedControl<T3D::EMapBuilderMeshSubMode>::Slot(T3D::EMapBuilderMeshSubMode::Spawn)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("MeshAddModeNameLabel", "Spawn Mesh"))
		+ SSegmentedControl<T3D::EMapBuilderMeshSubMode>::Slot(T3D::EMapBuilderMeshSubMode::Remove)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("MeshRemoveModeNameLabel", "Remove Mesh"))
		+ SSegmentedControl<T3D::EMapBuilderMeshSubMode>::Slot(T3D::EMapBuilderMeshSubMode::Select)
		  .Icon(FAppStyle::Get().GetBrush("ModelingToolsManagerCommands.BeginAddBoxPrimitiveTool"))
		  .Text(LOCTEXT("MeshSelectModeNameLabel", "Select Mesh"));

	T3D::NextVSlot(WidgetVerticalBox)
	[
		ModeSegmentedControl.ToSharedRef()
	];

	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(SBorder)
		.Visibility_Lambda([this]()
		{
			return GBuilderWidgetContext.MapBuilderMeshSubMode.Get() == T3D::EMapBuilderMeshSubMode::Spawn
				       ? EVisibility::Visible
				       : EVisibility::Collapsed;
		})
		[
			SNew(ST3DMeshPreviewWidget, T3DAsset)
		]
	];

	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(SBorder)
		.Visibility_Lambda([this]()
		{
			const bool bSelectedMode = GBuilderWidgetContext.MapBuilderMeshSubMode.Get() == T3D::EMapBuilderMeshSubMode::Select;
			const bool bSelectIndexValid = T3DAsset->Block.IsValidIndex(GBuilderWidgetContext.SelectedMeshBlockIndex.Get());
			
			return bSelectedMode && bSelectIndexValid ? EVisibility::Visible : EVisibility::Collapsed;
		})
		[
			SNew(ST3DMeshActorPreviewWidget, T3DAsset)
		]
	];

	ChildSlot
	[
		WidgetVerticalBox.ToSharedRef()
	];
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
