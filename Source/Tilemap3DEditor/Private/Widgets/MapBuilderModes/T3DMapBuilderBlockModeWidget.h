#pragma once

class ST3DSingleCubeBlockPreviewWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DSingleCubeBlockPreviewWidget)
	{
	}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const FT3DBlockConfig& InConfig);
private:
	TSharedPtr<FSlateBrush> PreviewTexBrush;
};

class ST3DBlockPreviewWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DBlockPreviewWidget)
	{
	}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TWeakObjectPtr<UT3DAsset>& InAsset);
private:
	TWeakObjectPtr<UT3DAsset> T3DAsset;
	TSharedPtr<SHorizontalBox> TileCubeBlockBox;
};

class TILEMAP3DEDITOR_API ST3DMapBuilderBlockModeWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DMapBuilderBlockModeWidget)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TWeakObjectPtr<UT3DAsset>& InAsset);

private:
	TSharedPtr<SSegmentedControl<T3D::EMapBuilderBlockSubMode>> ModeSegmentedControl;
	TWeakObjectPtr<UT3DAsset> T3DAsset;
};
