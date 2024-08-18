#include "T3DCommands.h"

#include "Components/StaticMeshComponent.h"
#include "Utility/MapBuildHelper.h"
#include "Generator/T3DTerrainGenerator.h"
#include "Widgets/T3DEditorSceneViewportClient.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"
#include "Materials/MaterialInstanceDynamic.h"

FT3DAddCubeCommand::FT3DAddCubeCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient,
                                       const int32 InIndex, const int32 InFloor)
	: Index(InIndex)
	  , Floor(InFloor)
	  , ViewportClient(InViewportClient)
{
}

void FT3DAddCubeCommand::Execute()
{
	const FT3DBlockConfig& BlockConfig = ViewportClient.Pin()->GetTilemapAsset()->GetBlockConfig(
		GBuilderWidgetContext.SelectedCubeBlockID.Get());
	FT3DTerrainGenerator::ModifyTerrainMesh(ViewportClient.Pin().Get(), Index, BlockConfig);
}

void FT3DAddCubeCommand::Undo()
{
	FT3DTerrainGenerator::ModifyTerrainMesh(ViewportClient.Pin().Get(), Index, FT3DBlockConfig::EmptyBlock);
}

FT3DRemoveCubeCommand::FT3DRemoveCubeCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient,
                                             const int32 InIndex, const int32 InFloor)
	: Index(InIndex)
	  , Floor(InFloor)
	  , ViewportClient(InViewportClient)
{
	UT3DAsset* Asset = ViewportClient.Pin()->GetTilemapAsset();
	BlockConfig = ViewportClient.Pin()->GetTilemapAsset()->GetBlockConfig(Asset->Block[InIndex].BlockID);
	BlockState = Asset->Block[Index].BlockState;
}

void FT3DRemoveCubeCommand::Execute()
{
	FT3DTerrainGenerator::ModifyTerrainMesh(ViewportClient.Pin().Get(), Index, FT3DBlockConfig::EmptyBlock);
}

void FT3DRemoveCubeCommand::Undo()
{
	FT3DTerrainGenerator::ModifyTerrainMesh(ViewportClient.Pin().Get(), Index, BlockConfig);
}

FT3DCleanupPlayerStartCommand::FT3DCleanupPlayerStartCommand(
	const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient)
	: ViewportClient(InViewportClient)
{
}

void FT3DCleanupPlayerStartCommand::Execute()
{
	UT3DAsset* Asset = ViewportClient.Pin()->GetTilemapAsset();
	OldIndex = Asset->PlayerStartLoc.Index;

	T3D::CleanupPlayerStartDecl(ViewportClient.Pin().Get());
}

void FT3DCleanupPlayerStartCommand::Undo()
{
	UDecalComponent* DecalComponent = T3D::SpawnDecalAtIndex(ViewportClient.Pin().Get(),
	                                                         GBuilderWidgetContext.DynamicPlayerStartMarkerMat,
	                                                         OldIndex);
	ViewportClient.Pin()->GetTilemapAsset()->PlayerStartLoc.Index = OldIndex;
	ViewportClient.Pin()->GetTilemapAsset()->PlayerStartLoc.Transform = FTransform::Identity;
	ViewportClient.Pin()->GetTilemapAsset()->PlayerStartLoc.MarkedDecal = DecalComponent;
}

FT3DCleanupPlayerPawnCommand::FT3DCleanupPlayerPawnCommand(
	const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InIndex)
	: ViewportClient(InViewportClient), OldIndex(InIndex)
{
}

void FT3DCleanupPlayerPawnCommand::Execute()
{
	T3D::CleanupPlayerPawnDecl(ViewportClient.Pin().Get(), OldIndex);
}

void FT3DCleanupPlayerPawnCommand::Undo()
{
	UDecalComponent* DecalComponent = T3D::SpawnDecalAtIndex(ViewportClient.Pin().Get(),
	                                                         GBuilderWidgetContext.DynamicPlayerPawnMarkerMat,
	                                                         OldIndex);

	UT3DAsset& Asset = *ViewportClient.Pin()->GetTilemapAsset();
	Asset.Block[OldIndex].PlayerPawnLoc.Index = OldIndex;
	Asset.Block[OldIndex].PlayerPawnLoc.MarkedDecal = DecalComponent;

	// ReSharper disable once CppExpressionWithoutSideEffects
	ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
}

FT3DSpawnPlayerPawnCommand::FT3DSpawnPlayerPawnCommand(
	const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient,
	const int32 InIndex)
	: Index(InIndex)
	  , ViewportClient(InViewportClient)
{
}

void FT3DSpawnPlayerPawnCommand::Execute()
{
	UDecalComponent* DecalComponent = T3D::SpawnDecalAtIndex(ViewportClient.Pin().Get(),
	                                                         GBuilderWidgetContext.DynamicPlayerPawnMarkerMat, Index);

	UT3DAsset& Asset = *ViewportClient.Pin()->GetTilemapAsset();
	Asset.Block[Index].PlayerPawnLoc.Index = Index;
	Asset.Block[Index].PlayerPawnLoc.MarkedDecal = DecalComponent;

	// ReSharper disable once CppExpressionWithoutSideEffects
	ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
}

void FT3DSpawnPlayerPawnCommand::Undo()
{
	T3D::CleanupPlayerPawnDecl(ViewportClient.Pin().Get(), Index);

	// ReSharper disable once CppExpressionWithoutSideEffects
	ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
}

FT3DRemovePlayerPawnCommand::FT3DRemovePlayerPawnCommand(
	const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InIndex)
	: Index(InIndex)
	  , ViewportClient(InViewportClient)
{
}

void FT3DRemovePlayerPawnCommand::Execute()
{
	T3D::CleanupPlayerPawnDecl(ViewportClient.Pin().Get(), Index);

	// ReSharper disable once CppExpressionWithoutSideEffects
	ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
}

void FT3DRemovePlayerPawnCommand::Undo()
{
	UDecalComponent* DecalComponent = T3D::SpawnDecalAtIndex(ViewportClient.Pin().Get(),
	                                                         GBuilderWidgetContext.DynamicPlayerPawnMarkerMat, Index);

	UT3DAsset& Asset = *ViewportClient.Pin()->GetTilemapAsset();
	Asset.Block[Index].PlayerPawnLoc.Index = Index;
	Asset.Block[Index].PlayerPawnLoc.MarkedDecal = DecalComponent;

	// ReSharper disable once CppExpressionWithoutSideEffects
	ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
}

FT3DSpawnPlayerStartCommand::FT3DSpawnPlayerStartCommand(
	const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InIndex)
	: Index(InIndex)
	  , ViewportClient(InViewportClient)
{
	OldIndex = INDEX_NONE;
}

void FT3DSpawnPlayerStartCommand::Execute()
{
	OldIndex = ViewportClient.Pin()->GetTilemapAsset()->PlayerStartLoc.Index;
	T3D::CleanupPlayerStartDecl(ViewportClient.Pin().Get());

	UDecalComponent* DecalComponent = T3D::SpawnDecalAtIndex(ViewportClient.Pin().Get(),
	                                                         GBuilderWidgetContext.DynamicPlayerStartMarkerMat, Index);
	ViewportClient.Pin()->GetTilemapAsset()->PlayerStartLoc.Index = Index;
	ViewportClient.Pin()->GetTilemapAsset()->PlayerStartLoc.Transform = FTransform::Identity;
	ViewportClient.Pin()->GetTilemapAsset()->PlayerStartLoc.MarkedDecal = DecalComponent;
}

void FT3DSpawnPlayerStartCommand::Undo()
{
	T3D::CleanupPlayerStartDecl(ViewportClient.Pin().Get());

	if (!ViewportClient.Pin()->GetTilemapAsset()->Block.IsValidIndex(OldIndex))
		return;

	UDecalComponent* DecalComponent = T3D::SpawnDecalAtIndex(ViewportClient.Pin().Get(),
	                                                         GBuilderWidgetContext.DynamicPlayerStartMarkerMat, OldIndex);
	ViewportClient.Pin()->GetTilemapAsset()->PlayerStartLoc.Index = OldIndex;
	ViewportClient.Pin()->GetTilemapAsset()->PlayerStartLoc.Transform = FTransform::Identity;
	ViewportClient.Pin()->GetTilemapAsset()->PlayerStartLoc.MarkedDecal = DecalComponent;
}

FT3DFillCommand::FT3DFillCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InFloor)
	: Floor(InFloor), ViewportClient(InViewportClient)
{
}

void FT3DFillCommand::Execute()
{
	UT3DAsset* Asset = ViewportClient.Pin()->GetTilemapAsset();
	ModifiedIndices.Empty();
	for (int32 Index = Asset->LevelSizeX * Asset->LevelSizeY * Floor; Index < Asset->LevelSizeX * Asset->LevelSizeY * (Floor + 1); ++Index)
	{
		if (Asset->Block[Index].BlockType == ET3DBlock::Air)
		{
			FT3DBlockConfig BlockConfig = ViewportClient.Pin()->GetTilemapAsset()->GetBlockConfig(
				GBuilderWidgetContext.SelectedCubeBlockID.Get());
			FT3DTerrainGenerator::ModifyTerrainMesh(ViewportClient.Pin().Get(), Index, BlockConfig);
			ModifiedIndices.Add(Index);
		}
	}
}

void FT3DFillCommand::Undo()
{
	for (const int32 Index : ModifiedIndices)
	{
		FT3DTerrainGenerator::ModifyTerrainMesh(ViewportClient.Pin().Get(), Index, FT3DBlockConfig::EmptyBlock);
	}
}

FT3DSpawnMeshCommand::FT3DSpawnMeshCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient,
	const FT3DMeshConfig& InMeshConfig,
	const int32 InIndex)
		:Index(InIndex), ViewportClient(InViewportClient), MeshConfig(InMeshConfig)
{
}

void FT3DSpawnMeshCommand::Execute()
{
	UT3DAsset* Asset = ViewportClient.Pin()->GetTilemapAsset();

	Asset->Block[Index].MeshLoc.ID = MeshConfig.ID;
	Asset->Block[Index].MeshLoc.Scale = FVector::OneVector;
	Asset->Block[Index].MeshLoc.Rotation = FRotator::ZeroRotator;
	Asset->Block[Index].MeshLoc.InstancedMeshActor = T3D::SpawnMeshAtIndex(ViewportClient.Pin().Get(), MeshConfig, Index);

	// ReSharper disable once CppExpressionWithoutSideEffects
	ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
}

void FT3DSpawnMeshCommand::Undo()
{
	UT3DAsset* Asset = ViewportClient.Pin()->GetTilemapAsset();

	Asset->Block[Index].MeshLoc.InstancedMeshActor->Destroy();
	Asset->Block[Index].MeshLoc.InstancedMeshActor = nullptr;
	Asset->Block[Index].MeshLoc.ID = NAME_None;

	// ReSharper disable once CppExpressionWithoutSideEffects
	ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
}

FT3DRemoveMeshCommand::FT3DRemoveMeshCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient,
	const int32 InIndex)
	:Index(InIndex), ViewportClient(InViewportClient)
{
}

void FT3DRemoveMeshCommand::Execute()
{
	UT3DAsset* Asset = ViewportClient.Pin()->GetTilemapAsset();
	
	MeshConfig = ViewportClient.Pin()->GetTilemapAsset()->GetMeshConfig(Asset->Block[Index].MeshLoc.ID);
	
	Asset->Block[Index].MeshLoc.InstancedMeshActor->Destroy();
	Asset->Block[Index].MeshLoc.InstancedMeshActor = nullptr;
	Asset->Block[Index].MeshLoc.ID = NAME_None;

	// ReSharper disable once CppExpressionWithoutSideEffects
	ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
}

void FT3DRemoveMeshCommand::Undo()
{
	UT3DAsset* Asset = ViewportClient.Pin()->GetTilemapAsset();

	Asset->Block[Index].MeshLoc.ID = MeshConfig.ID;
	Asset->Block[Index].MeshLoc.Scale = FVector::OneVector;
	Asset->Block[Index].MeshLoc.Rotation = FRotator::ZeroRotator;
	Asset->Block[Index].MeshLoc.InstancedMeshActor = T3D::SpawnMeshAtIndex(ViewportClient.Pin().Get(), MeshConfig, Index);

	// ReSharper disable once CppExpressionWithoutSideEffects
	ViewportClient.Pin()->GetTilemapAsset()->MarkPackageDirty();
}

FT3DModifyMeshScaleX::FT3DModifyMeshScaleX(const TWeakObjectPtr<UT3DAsset>& InAsset,
	const int32 InIndex, const float InValue)
	:Index(InIndex), NewValue(InValue), OldValue(0), Asset(InAsset)
{
}

void FT3DModifyMeshScaleX::Execute()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	OldValue = Block.MeshLoc.Scale.X;
	Block.MeshLoc.Scale.X = NewValue;
	Block.MeshLoc.InstancedMeshActor->SetActorScale3D(Block.MeshLoc.Scale);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

void FT3DModifyMeshScaleX::Undo()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	Block.MeshLoc.Scale.X = OldValue;
	Block.MeshLoc.InstancedMeshActor->SetActorScale3D(Block.MeshLoc.Scale);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

FT3DModifyMeshScaleY::FT3DModifyMeshScaleY(const TWeakObjectPtr<UT3DAsset>& InAsset,
	const int32 InIndex, const float InValue)
	:Index(InIndex), NewValue(InValue), OldValue(0), Asset(InAsset)
{
}


void FT3DModifyMeshScaleY::Execute()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	OldValue = Block.MeshLoc.Scale.Y;
	Block.MeshLoc.Scale.Y = NewValue;
	Block.MeshLoc.InstancedMeshActor->SetActorScale3D(Block.MeshLoc.Scale);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

void FT3DModifyMeshScaleY::Undo()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	Block.MeshLoc.Scale.Y = OldValue;
	Block.MeshLoc.InstancedMeshActor->SetActorScale3D(Block.MeshLoc.Scale);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

FT3DModifyMeshScaleZ::FT3DModifyMeshScaleZ(const TWeakObjectPtr<UT3DAsset>& InAsset,
	const int32 InIndex, const float InValue)
	:Index(InIndex), NewValue(InValue), OldValue(0), Asset(InAsset)
{
}

void FT3DModifyMeshScaleZ::Execute()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	OldValue = Block.MeshLoc.Scale.Z;
	Block.MeshLoc.Scale.Z = NewValue;
	Block.MeshLoc.InstancedMeshActor->SetActorScale3D(Block.MeshLoc.Scale);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

void FT3DModifyMeshScaleZ::Undo()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	Block.MeshLoc.Scale.Z = OldValue;
	Block.MeshLoc.InstancedMeshActor->SetActorScale3D(Block.MeshLoc.Scale);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

FT3DModifyMeshRotatorYaw::FT3DModifyMeshRotatorYaw(const TWeakObjectPtr<UT3DAsset>& InAsset,
	const int32 InIndex, const float InValue)
	:Index(InIndex), NewValue(InValue), OldValue(0), Asset(InAsset)
{
}

void FT3DModifyMeshRotatorYaw::Execute()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	OldValue = Block.MeshLoc.Rotation.Yaw;
	Block.MeshLoc.Rotation.Yaw = NewValue;
	Block.MeshLoc.InstancedMeshActor->SetActorRotation(Block.MeshLoc.Rotation);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

void FT3DModifyMeshRotatorYaw::Undo()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	Block.MeshLoc.Rotation.Yaw = OldValue;
	Block.MeshLoc.InstancedMeshActor->SetActorRotation(Block.MeshLoc.Rotation);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

FT3DModifyMeshRotatorPitch::FT3DModifyMeshRotatorPitch(const TWeakObjectPtr<UT3DAsset>& InAsset,
	const int32 InIndex, const float InValue)
	:Index(InIndex), NewValue(InValue), OldValue(0), Asset(InAsset)
{
}

void FT3DModifyMeshRotatorPitch::Execute()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	OldValue = Block.MeshLoc.Rotation.Pitch;
	Block.MeshLoc.Rotation.Pitch = NewValue;
	Block.MeshLoc.InstancedMeshActor->SetActorRotation(Block.MeshLoc.Rotation);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

void FT3DModifyMeshRotatorPitch::Undo()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	Block.MeshLoc.Rotation.Pitch = OldValue;
	Block.MeshLoc.InstancedMeshActor->SetActorRotation(Block.MeshLoc.Rotation);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

FT3DModifyMeshRotatorRoll::FT3DModifyMeshRotatorRoll(const TWeakObjectPtr<UT3DAsset>& InAsset,
	const int32 InIndex, const float InValue)
	:Index(InIndex), NewValue(InValue), OldValue(0), Asset(InAsset)
{
}

void FT3DModifyMeshRotatorRoll::Execute()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	OldValue = Block.MeshLoc.Rotation.Roll;
	Block.MeshLoc.Rotation.Roll = NewValue;
	Block.MeshLoc.InstancedMeshActor->SetActorRotation(Block.MeshLoc.Rotation);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}

void FT3DModifyMeshRotatorRoll::Undo()
{
	if (!Asset->Block.IsValidIndex(Index))
		return;

	FT3DBlock& Block = Asset->Block[Index];

	if (Block.MeshLoc.InstancedMeshActor == nullptr)
		return;

	Block.MeshLoc.Rotation.Roll = OldValue;
	Block.MeshLoc.InstancedMeshActor->SetActorRotation(Block.MeshLoc.Rotation);

	// ReSharper disable once CppExpressionWithoutSideEffects
	Asset->MarkPackageDirty();
}