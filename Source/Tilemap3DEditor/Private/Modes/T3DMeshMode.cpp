#include "T3DMeshMode.h"

#include "Command/T3DCommands.h"
#include "Utility/MapBuildHelper.h"
#include "Widgets/T3DEditorSceneViewportClient.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

void FT3DMeshMode::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if (EventArgs.Event != IE_Pressed)
		return;

	if (GBuilderWidgetContext.MapBuilderMeshSubMode.Get() == T3D::EMapBuilderMeshSubMode::Spawn)
	{
		FHitResult HitResult;
		T3D::ViewportMouseLineTrace(ViewportClient.Pin().Get(), T3DTerrainEditorClickTrace, HitResult);

		if (!HitResult.IsValidBlockingHit())
			return;

		FVector HitLocation = HitResult.Location;
		HitLocation.Z -= ViewportClient.Pin()->GetTilemapAsset()->GridSize * 0.5f;
		const int32 Index = ViewportClient.Pin()->GetTilemapAsset()->VectorToIndex(HitLocation);

		if (!ViewportClient.Pin()->GetTilemapAsset()->Block.IsValidIndex(Index))
			return;

		if (EventArgs.Key != EKeys::LeftMouseButton)
			return;
		
		if (ViewportClient.Pin()->GetTilemapAsset()->Block[Index].MeshLoc.InstancedMeshActor != nullptr)
		{
			return;
		}

		const FT3DMeshConfig MeshConfig = ViewportClient.Pin()->GetTilemapAsset()->GetMeshConfig(GBuilderWidgetContext.SelectedMeshBlockID.Get());

		GBuilderWidgetContext.Invoker->Execute(new FT3DSpawnMeshCommand(ViewportClient.Pin(), MeshConfig, Index));
	}

	if (GBuilderWidgetContext.MapBuilderMeshSubMode.Get() == T3D::EMapBuilderMeshSubMode::Remove)
	{
		FHitResult HitResult;
		T3D::ViewportMouseLineTrace(ViewportClient.Pin().Get(), T3DTerrainEditorClickTrace, HitResult);

		if (!HitResult.IsValidBlockingHit())
			return;

		FVector HitLocation = HitResult.Location;
		HitLocation.Z -= ViewportClient.Pin()->GetTilemapAsset()->GridSize * 0.5f;
		const int32 Index = ViewportClient.Pin()->GetTilemapAsset()->VectorToIndex(HitLocation);

		if (!ViewportClient.Pin()->GetTilemapAsset()->Block.IsValidIndex(Index))
			return;
		
		if (EventArgs.Key != EKeys::LeftMouseButton)	
			return;
		
		if (ViewportClient.Pin()->GetTilemapAsset()->Block[Index].MeshLoc.InstancedMeshActor == nullptr)
		{
			return;
		}

		GBuilderWidgetContext.Invoker->Execute(new FT3DRemoveMeshCommand(ViewportClient.Pin(), Index));
	}

	if (GBuilderWidgetContext.MapBuilderMeshSubMode.Get() == T3D::EMapBuilderMeshSubMode::Select)
	{
		FHitResult HitResult;
		T3D::ViewportMouseLineTrace(ViewportClient.Pin().Get(), T3DTerrainEditorMeshClickTrace, HitResult);

		if (!HitResult.IsValidBlockingHit())
			return;

		int32 ResIndex = INDEX_NONE;
		for (int32 Index = 0; Index < ViewportClient.Pin()->GetTilemapAsset()->Block.Num(); ++Index)
		{
			const FT3DBlock Block = ViewportClient.Pin()->GetTilemapAsset()->Block[Index];
			if (Block.MeshLoc.InstancedMeshActor == HitResult.GetActor())
			{
				ResIndex = Index;
				break;
			}
		}

		GBuilderWidgetContext.SelectedMeshBlockIndex = ResIndex;
	}
}

void FT3DMeshMode::Tick(float DeltaSeconds)
{
}
