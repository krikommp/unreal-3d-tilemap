#include "T3DPlayerStartMode.h"

#include "Command/T3DCommands.h"
#include "Widgets/T3DEditorSceneViewportClient.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"
#include "Utility/MapBuildHelper.h"

void FT3DPlayerStartMode::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if (EventArgs.Key == EKeys::LeftMouseButton && EventArgs.Event == IE_Pressed)
	{
		FHitResult HitResult;
		T3D::ViewportMouseLineTrace(ViewportClient.Pin().Get(), T3DTerrainEditorClickTrace, HitResult);

		if (HitResult.IsValidBlockingHit())
		{
			FVector HitLocation = HitResult.Location;
			HitLocation.Z -= ViewportClient.Pin()->GetTilemapAsset()->GridSize * 0.5f;
			const int32 Index = ViewportClient.Pin()->GetTilemapAsset()->VectorToIndex(HitLocation);

			if (!ViewportClient.Pin()->GetTilemapAsset()->Block.IsValidIndex(Index))
			{
				return;
			}

			GBuilderWidgetContext.Invoker->Execute(new FT3DSpawnPlayerStartCommand(ViewportClient.Pin(), Index));
			
			// ReSharper disable once CppExpressionWithoutSideEffects
			ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
		}
	}
}

void FT3DPlayerStartMode::Tick(float DeltaSeconds)
{
}
