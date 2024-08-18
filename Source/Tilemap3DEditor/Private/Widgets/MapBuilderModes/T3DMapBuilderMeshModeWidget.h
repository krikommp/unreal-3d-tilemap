#pragma once

class ST3DMeshActorPreviewWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DMeshActorPreviewWidget)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TWeakObjectPtr<UT3DAsset>& InAsset);	
};

class ST3DSingleMeshPreviewWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DSingleMeshPreviewWidget)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const FT3DMeshConfig& InConfig);
	
private:
	TSharedPtr<FSlateBrush> PreviewTexBrush;
};

class ST3DMeshPreviewWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DMeshPreviewWidget)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TWeakObjectPtr<UT3DAsset>& InAsset);
	
private:
	TSharedPtr<SSegmentedControl<T3D::EMapBuilderMeshSubMode>> ModeSegmentedControl;
	TWeakObjectPtr<UT3DAsset> T3DAsset;
	TSharedPtr<SHorizontalBox> TileMeshBlockBox;
};

class ST3DMapBuilderMeshModeWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DMapBuilderMeshModeWidget)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TWeakObjectPtr<UT3DAsset>& InAsset);
	
private:
	TSharedPtr<SSegmentedControl<T3D::EMapBuilderMeshSubMode>> ModeSegmentedControl;
	TWeakObjectPtr<UT3DAsset> T3DAsset;
};
