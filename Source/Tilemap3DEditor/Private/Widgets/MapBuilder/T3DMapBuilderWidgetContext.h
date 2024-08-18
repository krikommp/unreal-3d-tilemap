#pragma once

#include "Utility/ValueWatcher.h"
#include "Command/T3DInvoker.h"

struct FT3DMapBuilderWidgetContext
{
	TValueWatcher<bool> bMapBuilderEditing = false;
	TValueWatcher<bool> bHalfBlock = false;
	TValueWatcher<bool> bFillPaint = false;
	TValueWatcher<T3D::EMapBuilderMode> MapBuilderMode = T3D::EMapBuilderMode::View;
	TValueWatcher<T3D::EMapBuilderBlockSubMode> MapBuilderBlockSubMode = T3D::EMapBuilderBlockSubMode::Add;
	TValueWatcher<T3D::EMapBuilderMeshSubMode> MapBuilderMeshSubMode = T3D::EMapBuilderMeshSubMode::Spawn;
	TValueWatcher<T3D::EMapBuilderAIPawnMode> MapBuilderAIPawnMode = T3D::EMapBuilderAIPawnMode::Spawn;
	TValueWatcher<T3D::EMapBuilderPlayerPawnMode> MapBuilderPlayerPawnMode = T3D::EMapBuilderPlayerPawnMode::Spawn;
	TValueWatcher<T3D::EMapBuilderPlayerStartMode> MapBuilderPlayerStartMode = T3D::EMapBuilderPlayerStartMode::Spawn;
	TValueWatcher<FName> SelectedCubeBlockID = NAME_None;
	TValueWatcher<FName> SelectedMeshBlockID = NAME_None;
	TValueWatcher<int32> SelectedMeshBlockIndex = INDEX_NONE;
	TObjectPtr<UMaterialInstanceDynamic> DynamicTerrainMaterial;
	TObjectPtr<UMaterialInstanceDynamic> DynamicPlayerStartMarkerMat;
	TObjectPtr<UMaterialInstanceDynamic> DynamicPlayerPawnMarkerMat;

	TUniquePtr<FT3DInvoker> Invoker;
};

extern FT3DMapBuilderWidgetContext GBuilderWidgetContext;