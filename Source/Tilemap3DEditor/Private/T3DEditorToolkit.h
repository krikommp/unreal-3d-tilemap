#pragma once

class ST3DEditorSceneViewport;
class ST3DPropertiesTabBody;

class FT3DEditorToolkit final : public FAssetEditorToolkit, public FGCObject
{
	static const FName ViewportID;
	static const FName DetailsID;
public:
	FT3DEditorToolkit();

	//~ Begin IToolkit interface
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	//~ Begin IToolkit interface

	//~ Begin FAssetEditorToolkit interface
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	//~ Begin FAssetEditorToolkit interface

	//~ Begin FSerializableObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;
	//~ Begin FSerializableObject interface
	
	void Initialize(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UT3DAsset* Asset);

	void BindCommand();

	void OnUndoBuilderInvoked();

private:
	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args) const;
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args) const;

	TWeakObjectPtr<UT3DAsset> T3DAsset;
	TSharedPtr<ST3DEditorSceneViewport> Viewport;
	TSharedPtr<ST3DPropertiesTabBody> PropertiesTabBody;
};
