#pragma once

class FT3DEditorSceneViewportClient;
class UDecalComponent;

namespace T3D
{
	bool ViewportMouseLineTrace(FT3DEditorSceneViewportClient* ViewportClient, ECollisionChannel CollisionChannel, FHitResult& OutHitResult);
	
	UDecalComponent* SpawnDecalAtLocation(FT3DEditorSceneViewportClient* ViewportClient, UMaterialInterface* DecalMaterial, const FVector& Location);
	UDecalComponent* SpawnDecalAtIndex(FT3DEditorSceneViewportClient* ViewportClient, UMaterialInterface* DecalMaterial, const int32 Index);

	AActor* SpawnMeshAtLocation(FT3DEditorSceneViewportClient* ViewportClient, const FT3DMeshConfig& MeshConfig, const FVector& Location);
	AActor* SpawnMeshAtIndex(FT3DEditorSceneViewportClient* ViewportClient, const FT3DMeshConfig& MeshConfig, const int32 Index);

	void CleanupPlayerStartDecl(FT3DEditorSceneViewportClient* ViewportClient);
	void CleanupPlayerPawnDecl(FT3DEditorSceneViewportClient* ViewportClient, const int32 Index);

	UTexture2D* GetThumbnailFromStaticMesh(UStaticMesh* Mesh);
}
