#include "T3DEditorSceneViewport.h"

#include "T3DEditorSceneViewportClient.h"

void ST3DEditorSceneViewport::Construct(const FArguments& InArgs, UT3DAsset* InAsset)
{
	T3DAsset = InAsset;
	PreviewScene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
	PreviewScene->SetFloorVisibility(false, false);
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

TSharedRef<SEditorViewport> ST3DEditorSceneViewport::GetViewportWidget()
{
	return SharedThis(this);
}

TSharedPtr<FExtender> ST3DEditorSceneViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

void ST3DEditorSceneViewport::OnFloatingButtonClicked()
{
}

TSharedPtr<SWidget> ST3DEditorSceneViewport::MakeViewportToolbar()
{
	return SNew(SCommonEditorViewportToolbarBase, SharedThis(this));
}

TSharedRef<FEditorViewportClient> ST3DEditorSceneViewport::MakeEditorViewportClient()
{
	if (!T3DAssetPreviewClient.IsValid())
	{
		T3DAssetPreviewClient = MakeShared<FT3DEditorSceneViewportClient>(T3DAsset, PreviewScene.Get());
		T3DAssetPreviewClient->OnConstruction();
	}

	return T3DAssetPreviewClient.ToSharedRef();
}
