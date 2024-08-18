#include "T3DPlayerPawnMode.h"

#include "Command/T3DCommands.h"
#include "Utility/MapBuildHelper.h"
#include "Widgets/T3DEditorSceneViewportClient.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

void FT3DPlayerPawnMode::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if (EventArgs.Key != EKeys::LeftMouseButton || EventArgs.Event != IE_Pressed)
		return;

	FHitResult HitResult;
	T3D::ViewportMouseLineTrace(ViewportClient.Pin().Get(), T3DTerrainEditorClickTrace, HitResult);

	if (!HitResult.IsValidBlockingHit())
		return;

	FVector HitLocation = HitResult.Location;
	HitLocation.Z -= ViewportClient.Pin()->GetTilemapAsset()->GridSize * 0.5f;
	const int32 Index = ViewportClient.Pin()->GetTilemapAsset()->VectorToIndex(HitLocation);

	if (!ViewportClient.Pin()->GetTilemapAsset()->Block.IsValidIndex(Index))
		return;

	if (GBuilderWidgetContext.MapBuilderPlayerPawnMode.Get() == T3D::EMapBuilderPlayerPawnMode::Spawn)
		GBuilderWidgetContext.Invoker->Execute(new FT3DSpawnPlayerPawnCommand(ViewportClient.Pin(), Index));
	else if (GBuilderWidgetContext.MapBuilderPlayerPawnMode.Get() == T3D::EMapBuilderPlayerPawnMode::Remove)
		GBuilderWidgetContext.Invoker->Execute(new FT3DRemovePlayerPawnCommand(ViewportClient.Pin(), Index));
}

void FT3DPlayerPawnMode::Tick(float DeltaSeconds)
{
}
