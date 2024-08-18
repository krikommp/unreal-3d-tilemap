#include "FT3DBlockEditMode.h"

#include "ProceduralMeshComponent.h"
#include "Command/T3DCommands.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utility/MapBuildHelper.h"
#include "Widgets/T3DEditorSceneViewportClient.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

void FT3DBlockEditMode::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if (EventArgs.Key == EKeys::LeftMouseButton && EventArgs.Event == IE_Pressed)
	{
		FHitResult HitResult;
		T3D::ViewportMouseLineTrace(ViewportClient.Pin().Get(), T3DTerrainEditorClickTrace, HitResult);

		if (HitResult.IsValidBlockingHit())
		{
			UT3DAsset* Asset = ViewportClient.Pin()->GetTilemapAsset();
		 	const int32 Floor = ViewportClient.Pin()->GetTilemapAsset()->VectorToFloor(HitResult.Location);
			const int32 Index = ViewportClient.Pin()->GetTilemapAsset()->VectorToIndex(HitResult.Location, Floor);
			
			// before add/remove anyone block, we need to clean up some data such as decal, player pawn, etc.
			const int32 AboveIndex = ViewportClient.Pin()->GetTilemapAsset()->VectorToIndex(HitResult.Location, FMath::Max(0, Floor - 1));
			if (Asset->Block[AboveIndex].PlayerPawnLoc.MarkedDecal)
			{
				GBuilderWidgetContext.Invoker->Execute(new FT3DCleanupPlayerPawnCommand(ViewportClient.Pin(), AboveIndex));
			}
			if (Asset->PlayerStartLoc.Index == Index)
			{
				GBuilderWidgetContext.Invoker->Execute(new FT3DCleanupPlayerStartCommand(ViewportClient.Pin()));
			}
			
			if (GBuilderWidgetContext.MapBuilderBlockSubMode.Get() == T3D::EMapBuilderBlockSubMode::Add)
			{
				if (GBuilderWidgetContext.bFillPaint.Get())
					GBuilderWidgetContext.Invoker->Execute(new FT3DFillCommand(ViewportClient.Pin(), Floor));
				else
					GBuilderWidgetContext.Invoker->Execute(new FT3DAddCubeCommand(ViewportClient.Pin(), Index, Floor));
			}else
			{
				if (Asset->Block[Index].BlockType != ET3DBlock::Air)
				{
					GBuilderWidgetContext.Invoker->Execute(new FT3DRemoveCubeCommand(ViewportClient.Pin(), Index, Floor));
				}
			}
			
			// ReSharper disable once CppExpressionWithoutSideEffects
			ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
		}
	}
}

void FT3DBlockEditMode::Tick(float DeltaSeconds)
{
}
