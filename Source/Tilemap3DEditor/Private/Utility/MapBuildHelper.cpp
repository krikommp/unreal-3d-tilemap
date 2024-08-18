#include "MapBuildHelper.h"

#include "IImageWrapperModule.h"
#include "ImageUtils.h"
#include "ObjectTools.h"
#include "Components/DecalComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/T3DEditorSceneViewportClient.h"

bool T3D::ViewportMouseLineTrace(FT3DEditorSceneViewportClient* ViewportClient, ECollisionChannel CollisionChannel, FHitResult& OutHitResult)
{
	const auto CursorLocation = ViewportClient->GetCursorWorldLocationFromMousePos();

	const TArray<AActor*> IgnoreActor;
	UKismetSystemLibrary::LineTraceSingle(
		ViewportClient->GetWorld(),
		CursorLocation.GetOrigin(),
		CursorLocation.GetOrigin() + CursorLocation.GetDirection() * 10000.f,
		UEngineTypes::ConvertToTraceType(CollisionChannel),
		false,
		IgnoreActor,
		EDrawDebugTrace::None,
		OutHitResult,
		false
	);

	return OutHitResult.IsValidBlockingHit();
}

UDecalComponent* T3D::SpawnDecalAtLocation(FT3DEditorSceneViewportClient* ViewportClient, UMaterialInterface* DecalMaterial, const FVector& Location)
{
	FTransform Transform = FTransform::Identity;
	Transform.SetLocation(Location);
	Transform.SetRotation(FQuat({90.0f, 0.0f, 0.0f}));

	const FVector DecalSize = { 95.0f, 45.0f, 45.0f };
	UDecalComponent* DecalComponent = NewObject<UDecalComponent>();
	ViewportClient->GetPreviewScene()->AddComponent(DecalComponent, Transform);
	DecalComponent->bAllowAnyoneToDestroyMe = true;
	DecalComponent->SetDecalMaterial(DecalMaterial);
	DecalComponent->DecalSize = DecalSize;
	DecalComponent->SetUsingAbsoluteScale(true);

	return DecalComponent;
}

UDecalComponent* T3D::SpawnDecalAtIndex(FT3DEditorSceneViewportClient* ViewportClient, UMaterialInterface* DecalMaterial, const int32 Index)
{
	FVector Location = ViewportClient->GetTilemapAsset()->IndexToVector(Index);
	Location.Z = Index / (ViewportClient->GetTilemapAsset()->LevelSizeX * ViewportClient->GetTilemapAsset()->LevelSizeY) * ViewportClient->GetTilemapAsset()->GridSize + ViewportClient->GetTilemapAsset()->GridSize;
	Location.Z += 1.0f;

	return SpawnDecalAtLocation(ViewportClient, DecalMaterial, Location);
}

AActor* T3D::SpawnMeshAtLocation(FT3DEditorSceneViewportClient* ViewportClient, const FT3DMeshConfig& MeshConfig, const FVector& Location)
{
	const auto Actor = ViewportClient->GetWorld()->SpawnActor<AActor>();
	
	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Actor->AddComponentByClass(UStaticMeshComponent::StaticClass(), false, FTransform::Identity, false));
	StaticMeshComponent->SetStaticMesh(MeshConfig.Mesh);
	StaticMeshComponent->SetMaterial(0, MeshConfig.Material);
	StaticMeshComponent->SetMobility(EComponentMobility::Static);
	StaticMeshComponent->SetCollisionResponseToChannel(T3DTerrainEditorMeshClickTrace, ECR_Block);
	
	Actor->SetActorLocation(Location);

	return Actor;
}

AActor* T3D::SpawnMeshAtIndex(FT3DEditorSceneViewportClient* ViewportClient, const FT3DMeshConfig& MeshConfig, const int32 Index)
{
	FVector Location = ViewportClient->GetTilemapAsset()->IndexToVector(Index);
	Location.Z = Index / (ViewportClient->GetTilemapAsset()->LevelSizeX * ViewportClient->GetTilemapAsset()->LevelSizeY) * ViewportClient->GetTilemapAsset()->GridSize + ViewportClient->GetTilemapAsset()->GridSize;
	Location.Z += 1.0f;

	return SpawnMeshAtLocation(ViewportClient, MeshConfig, Location);
}

void T3D::CleanupPlayerStartDecl(FT3DEditorSceneViewportClient* ViewportClient)
{
	UT3DAsset* Asset = ViewportClient->GetTilemapAsset();

	FT3DPlayerStartLoc& PlayerStartLoc = Asset->PlayerStartLoc;
	if (PlayerStartLoc.MarkedDecal)
	{
		ViewportClient->GetPreviewScene()->RemoveComponent(PlayerStartLoc.MarkedDecal);
		PlayerStartLoc.MarkedDecal->DestroyComponent();
		PlayerStartLoc.MarkedDecal = nullptr;
	}
	PlayerStartLoc.Index = INDEX_NONE;
}

void T3D::CleanupPlayerPawnDecl(FT3DEditorSceneViewportClient* ViewportClient, const int32 Index)
{
	UT3DAsset* Asset = ViewportClient->GetTilemapAsset();

	FT3DPlayerPawnLoc& PlayerPawnLoc = Asset->Block[Index].PlayerPawnLoc;
	if (PlayerPawnLoc.MarkedDecal)
	{
		ViewportClient->GetPreviewScene()->RemoveComponent(PlayerPawnLoc.MarkedDecal);
		PlayerPawnLoc.MarkedDecal->DestroyComponent();
		PlayerPawnLoc.MarkedDecal = nullptr;
	}
	PlayerPawnLoc.Index = INDEX_NONE;
}

UTexture2D* T3D::GetThumbnailFromStaticMesh(UStaticMesh* Mesh)
{
	UTexture2D* Texture = nullptr;

	const FAssetData AssetData = FAssetData(Mesh);
	const FName ObjectFullName = FName(*AssetData.GetFullName());
	FString PackageFileName;
	TSet<FName> ObjectFullNames;
	ObjectFullNames.Add(ObjectFullName);
	if (FPackageName::DoesPackageExist(AssetData.PackageName.ToString(), &PackageFileName))
	{
		FThumbnailMap ThumbnailMap;
		ThumbnailTools::LoadThumbnailsFromPackage(PackageFileName, ObjectFullNames, ThumbnailMap);
		FObjectThumbnail* ObjTN = ThumbnailMap.Find(ObjectFullName);

		IImageWrapperModule& ImageWrapperModule = FModuleManager::Get().LoadModuleChecked<IImageWrapperModule>(
			TEXT("ImageWrapper"));
		TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

		ImageWrapper->SetRaw(ObjTN->GetUncompressedImageData().GetData(), ObjTN->GetUncompressedImageData().Num(),
							 ObjTN->GetImageWidth(), ObjTN->GetImageHeight(), ERGBFormat::BGRA, 8);
		const TArray64<uint8>& CompressedByteArray = ImageWrapper->GetCompressed();

		Texture = FImageUtils::ImportBufferAsTexture2D(CompressedByteArray);
	}

	return Texture;
}
