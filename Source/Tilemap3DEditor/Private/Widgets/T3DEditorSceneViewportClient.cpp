#include "T3DEditorSceneViewportClient.h"

#include "ProceduralMeshComponent.h"
#include "T3DEditorSettings.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Texture.h"
#include "Generator/T3DTerrainGenerator.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"
#include "Modes/FT3DBlockEditMode.h"
#include "Utility/MapBuildHelper.h"
#include "Utility/ValueWatcher.h"

FT3DEditorSceneViewportClient::FT3DEditorSceneViewportClient(TWeakObjectPtr<UT3DAsset> InAsset, FPreviewScene* InPreviewScene)
	: FEditorViewportClient(nullptr, InPreviewScene), Asset(InAsset)
{
	SetRealtime(true);
	SetViewLocation(FVector(0.f, 100.f, 100.f));
	SetLookAtLocation(FVector::Zero(), true);

	FCoreUObjectDelegates::OnObjectPropertyChanged.AddRaw(this, &FT3DEditorSceneViewportClient::OnUObjectPropertyChanged);
	GBuilderWidgetContext.MapBuilderMode.BindRaw(this, &FT3DEditorSceneViewportClient::OnBuildModeChanged);

	// 创建一系列场景可视化组件
	CollisionPlane = NewObject<UStaticMeshComponent>();
	PreviewScene->AddComponent(CollisionPlane, FTransform::Identity);
	CubeBlockTerrain = NewObject<UProceduralMeshComponent>();
	PreviewScene->AddComponent(CubeBlockTerrain, FTransform::Identity);

}

FT3DEditorSceneViewportClient::~FT3DEditorSceneViewportClient()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
	GBuilderWidgetContext.MapBuilderMode.Unbind(this);
}

void FT3DEditorSceneViewportClient::OnConstruction()
{
	OnBuildModeChanged(GBuilderWidgetContext.MapBuilderMode.Get());
	OnReCreateTerrainMat();
	OnReCreatePlayerStartMarkerMat();
	OnReCreatePlayerPawnMat();

	RebuildPreviewScene();
}

void FT3DEditorSceneViewportClient::Tick(float DeltaSeconds)
{
	if (EditMode.IsValid())
	{
		EditMode->Tick(DeltaSeconds);
	}
	FEditorViewportClient::Tick(DeltaSeconds);
}

bool FT3DEditorSceneViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if (EditMode.IsValid())
	{
		EditMode->InputKey(EventArgs);
	}
	return FEditorViewportClient::InputKey(EventArgs);
}

void FT3DEditorSceneViewportClient::OnUObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (Object->GetClass() == UT3DEditorSettings::StaticClass() && Object->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		RebuildPreviewScene();
	}
	// todo... update too frequently
	if (Object->GetClass() == UT3DAsset::StaticClass() && Object == Asset)
	{
		RebuildPreviewScene();
	}
	if (Object->GetClass() == UT3DConfigDataAsset::StaticClass())
	{
		if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UT3DConfigDataAsset, Textures))
		{
			OnReCreateTerrainMat();
		}

		if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UT3DConfigDataAsset, PlayerStartDecalColor))
		{
			OnReCreatePlayerStartMarkerMat();
		}

		if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UT3DConfigDataAsset, PlayerPawnDecalColor))
		{
			OnReCreatePlayerPawnMat();
		}
	}
}

void FT3DEditorSceneViewportClient::OnBuildModeChanged(const T3D::EMapBuilderMode& NewMode)
{
	if (EditMode.IsValid() && EditMode->GetBuilderMode() == NewMode)
	{
		return;
	}
	EditMode.Reset(FT3DEditModeFactory::CreateEditMode(NewMode, SharedThis(this)));
}

void FT3DEditorSceneViewportClient::OnReCreateTerrainMat() const
{
	if (GBuilderWidgetContext.DynamicTerrainMaterial == nullptr)
	{
		GBuilderWidgetContext.DynamicTerrainMaterial= UMaterialInstanceDynamic::Create(Asset->TilemapConfig->TerrainMaterial, PreviewScene->GetWorld());
	}
	
	GBuilderWidgetContext.DynamicTerrainMaterial->SetTextureParameterValue("MainTextures", Cast<UTexture>(Asset->TilemapConfig->Textures));
}

void FT3DEditorSceneViewportClient::OnReCreatePlayerStartMarkerMat() const
{
	if (GBuilderWidgetContext.DynamicPlayerStartMarkerMat == nullptr)
	{
		GBuilderWidgetContext.DynamicPlayerStartMarkerMat = UMaterialInstanceDynamic::Create(Asset->TilemapConfig->DecalMaterial, PreviewScene->GetWorld());
	}

	GBuilderWidgetContext.DynamicPlayerStartMarkerMat->SetVectorParameterValue("BaseColor", Asset->TilemapConfig->PlayerStartDecalColor);
}

void FT3DEditorSceneViewportClient::OnReCreatePlayerPawnMat() const
{
	if (GBuilderWidgetContext.DynamicPlayerPawnMarkerMat == nullptr)
	{
		GBuilderWidgetContext.DynamicPlayerPawnMarkerMat = UMaterialInstanceDynamic::Create(Asset->TilemapConfig->DecalMaterial, PreviewScene->GetWorld());
	}

	GBuilderWidgetContext.DynamicPlayerPawnMarkerMat->SetVectorParameterValue("BaseColor", Asset->TilemapConfig->PlayerPawnDecalColor);
}

void FT3DEditorSceneViewportClient::GetEditRangeScaleAndLocation(FVector& Location, float& ScaleX, float& ScaleY) const
{
	ScaleX = Asset->LevelSizeX * (Asset->GridSize / 200.0f);
	ScaleY = Asset->LevelSizeY * (Asset->GridSize / 200.0f);
	// 注意我们需要计算的是正中间
	const float X = (Asset->LevelSizeX * Asset->GridSize) / 2.0f - Asset->
		GridSize / 2.0f;
	const float Y = (Asset->LevelSizeY * Asset->GridSize) / 2.0f - Asset->
		GridSize / 2.0f;

	Location = FVector(X, Y, 0.f);
}

void FT3DEditorSceneViewportClient::RebuildPreviewScene()
{
	const UT3DEditorSettings* Settings = GetMutableDefault<UT3DEditorSettings>();
	
	if (Settings->CollisionPlaneMesh.LoadSynchronous())
	{
		CollisionPlane->SetStaticMesh(Settings->CollisionPlaneMesh.LoadSynchronous());
	}
	if (Settings->CollisionPlaneMat.LoadSynchronous())
	{
		CollisionPlane->SetMaterial(0, Settings->CollisionPlaneMat.LoadSynchronous());
	}
	CollisionPlane->SetCollisionResponseToChannel(T3DTerrainEditorClickTrace, ECR_Block);
	
	FTransform CollisionTransform;
	float CollisionScaleX, CollisionScaleY;
	FVector CollisionLocation;
	GetEditRangeScaleAndLocation(CollisionLocation, CollisionScaleX,
								 CollisionScaleY);
	CollisionTransform.SetLocation(CollisionLocation + FVector::Zero());
	CollisionTransform.SetScale3D(FVector(CollisionScaleX, CollisionScaleY, 1.0));
	CollisionPlane->SetWorldTransform(CollisionTransform);
	CollisionPlane->SetVisibility(true);
	CollisionPlane->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Asset->Block.SetNumZeroed(Asset->LevelSizeX * Asset->LevelSizeY * Asset->Floors);

	// recover saved data
	FT3DTerrainGenerator::Setup(this);
	Asset->PlayerStartLoc.MarkedDecal = T3D::SpawnDecalAtIndex(this, GBuilderWidgetContext.DynamicPlayerStartMarkerMat, Asset->PlayerStartLoc.Index);
	for (int32 Index = 0; Index < Asset->Block.Num(); ++Index)
	{
		if (Asset->Block[Index].PlayerPawnLoc.Index == Index)
		{
			Asset->Block[Index].PlayerPawnLoc.MarkedDecal = T3D::SpawnDecalAtIndex(this, GBuilderWidgetContext.DynamicPlayerPawnMarkerMat, Index);
		}
		if (Asset->Block[Index].MeshLoc.ID != NAME_None)
		{
			Asset->Block[Index].MeshLoc.InstancedMeshActor = T3D::SpawnMeshAtIndex(this, Asset->GetMeshConfig(Asset->Block[Index].MeshLoc.ID), Index);
			Asset->Block[Index].MeshLoc.InstancedMeshActor->SetActorScale3D(Asset->Block[Index].MeshLoc.Scale);
			Asset->Block[Index].MeshLoc.InstancedMeshActor->SetActorRotation(Asset->Block[Index].MeshLoc.Rotation);
		}
	}
}
