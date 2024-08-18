#pragma once

class UBoxComponent;
class UProceduralMeshComponent;
class FT3DEditModeBase;

class FT3DEditorSceneViewportClient final : public FEditorViewportClient, public TSharedFromThis<FT3DEditorSceneViewportClient>
{
public:
	explicit FT3DEditorSceneViewportClient(TWeakObjectPtr<UT3DAsset> InAsset, FPreviewScene* InPreviewScene);
	virtual ~FT3DEditorSceneViewportClient() override;
	void OnConstruction();
	virtual void Tick(float DeltaSeconds) override;
	virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;

private:
	void OnUObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);
	void OnBuildModeChanged(const T3D::EMapBuilderMode& NewMode);
	void OnReCreateTerrainMat() const;
	void OnReCreatePlayerStartMarkerMat() const;
	void OnReCreatePlayerPawnMat() const;
	void GetEditRangeScaleAndLocation(FVector& Location, float& ScaleX, float& ScaleY) const;
public:
	void RebuildPreviewScene();
	UT3DAsset* GetTilemapAsset() const { return Asset.Get(); }
	UProceduralMeshComponent* GetTerrainMesh() const { return CubeBlockTerrain; }
	
private:
	TObjectPtr<UStaticMeshComponent> CollisionPlane;
	TObjectPtr<UProceduralMeshComponent> CubeBlockTerrain;

	TWeakObjectPtr<UT3DAsset> Asset;

	TUniquePtr<FT3DEditModeBase> EditMode;
};
