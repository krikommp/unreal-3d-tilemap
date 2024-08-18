#pragma once

class FT3DEditorSceneViewportClient;

class ST3DEditorSceneViewport final : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider
{
public:
	SLATE_BEGIN_ARGS(ST3DEditorSceneViewport)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UT3DAsset* InAsset);
	
	// ICommonEditorViewportToolbarInfoProvider interface
	virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;
	// End of ICommonEditorViewportToolbarInfoProvider interface

	// SEditorViewport interface
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
	// End of SEditorViewport interface
	
	FT3DEditorSceneViewportClient* GetSceneViewportClient() const { return T3DAssetPreviewClient.Get(); }

protected:
	// SEditorViewport interface
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	// End of SEditorViewport interface

private:
	TWeakObjectPtr<UT3DAsset> T3DAsset;
	TSharedPtr<FAdvancedPreviewScene> PreviewScene;
	TSharedPtr<FT3DEditorSceneViewportClient> T3DAssetPreviewClient;
};
