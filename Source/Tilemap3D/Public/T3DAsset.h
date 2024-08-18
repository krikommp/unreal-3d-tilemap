#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "T3DAsset.generated.h"

class UT3DPawnInterface;
class UDecalComponent;
class UTexture2D;
class UStaticMesh;
class UMaterialInterface;
class UTexture2DArray;
class UDataTable;

UENUM(BlueprintType)
enum class ET3DBlock : uint8
{
	Air = 0,
	Cube = 1,
	Mesh = 2,
	Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ET3DBlockState : uint8
{
	Full = 0,
	Half = 1,
	Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ET3DBlockDirection : uint8
{
	Forward = 0,
	Right = 1,
	Back = 2,
	Left = 3,
	Up = 4,
	Down = 5
};

USTRUCT(BlueprintType)
struct TILEMAP3D_API FT3DPlayerStartLoc
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTransform Transform = FTransform::Identity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Index = INDEX_NONE;

#if WITH_EDITORONLY_DATA
	UPROPERTY(Transient)
	TObjectPtr<UDecalComponent> MarkedDecal;
#endif
};

USTRUCT(BlueprintType)
struct TILEMAP3D_API FT3DPlayerPawnLoc
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Index = INDEX_NONE;

#if WITH_EDITORONLY_DATA
	UPROPERTY(Transient)
	TObjectPtr<UDecalComponent> MarkedDecal;
#endif
};

USTRUCT(BlueprintType)
struct TILEMAP3D_API FT3DMeshLoc 
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName ID = NAME_None;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector Scale = FVector::OneVector;

#if WITH_EDITORONLY_DATA
	UPROPERTY(Transient)
	TObjectPtr<AActor> InstancedMeshActor;
#endif
};

USTRUCT(BlueprintType)
struct TILEMAP3D_API FT3DBlock
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName BlockID = NAME_None;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ET3DBlock BlockType = ET3DBlock::Air;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ET3DBlockState BlockState = ET3DBlockState::Full;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FT3DPlayerPawnLoc PlayerPawnLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FT3DMeshLoc MeshLoc;
};

USTRUCT(BlueprintType)
struct TILEMAP3D_API FT3DGameBoardData 
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FVector> Vertices;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<int32> Triangles;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FVector> Normals;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FColor> Colors;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FVector2D> UV0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 VertexCount = 0;
};

USTRUCT(BlueprintType)
struct TILEMAP3D_API FT3DpPathFinding
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 Index = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite)
	int32 Cost = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite)
	int32 Parent = INDEX_NONE;
};

USTRUCT(BlueprintType)
struct TILEMAP3D_API FT3DPathFindingEdge 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Index = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Cost = INDEX_NONE;
};

USTRUCT(BlueprintType)
struct TILEMAP3D_API FT3DPathFindingBlock
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector Location = FVector::Zero();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<int32> EdgeArrayIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FT3DPathFindingEdge> EdgeArray;
};

USTRUCT(BlueprintType)
struct TILEMAP3D_API FT3DBlockConfig 
{
	GENERATED_BODY()

	static FT3DBlockConfig EmptyBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ET3DBlock BlockType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UTexture2D>> BlockTextures;
};

USTRUCT(BlueprintType)
struct TILEMAP3D_API FT3DMeshConfig 
{
	GENERATED_BODY()

	static FT3DMeshConfig EmptyBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> Material;
};

UCLASS(BlueprintType, meta=(DisplayName = "3D Tilemap Config"))
class TILEMAP3D_API UT3DConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2DArray> Textures;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> TerrainMaterial;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> DecalMaterial;

	UPROPERTY(EditAnywhere)
	TArray<FT3DBlockConfig> BlockConfigs;

	UPROPERTY(EditAnywhere)
	TArray<FT3DMeshConfig> MeshConfigs;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UDataTable> NeedSpawnToGameBroadPawnData;
	
	UPROPERTY(EditAnywhere)
	FLinearColor PlayerStartDecalColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere)
	FLinearColor PlayerPawnDecalColor = FLinearColor::Blue;

#if WITH_EDITORONLY_DATA
 	UPROPERTY(Transient)
 	TMap<FName, TWeakObjectPtr<UT3DPawnInterface>> CachedLoadedPawnData;
#endif
};

UCLASS(NotBlueprintable, BlueprintType)
class TILEMAP3D_API UT3DAsset : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Level Values")
	int32 Floors = 0;

	UPROPERTY(EditAnywhere, Category="Level Values", meta=(DisplayName="LevelWidth"))
	int32 LevelSizeX = 0;

	UPROPERTY(EditAnywhere, Category="Level Values", meta=(DisplayName="LevelDepth"))
	int32 LevelSizeY = 0;

	UPROPERTY(VisibleAnywhere, Category="Path Finding")
	int32 LevelSizeZ = 1;

	UPROPERTY(EditAnywhere, Category="Grid Values")
	int32 GridSize = 100;

	UPROPERTY(EditAnywhere, Category="Path Finding")
	int32 HeightSlowIncrement = 100;
	
	UPROPERTY(EditAnywhere, Category="Path Finding")
	int32 HeightBetweenLevel = 200;

	UPROPERTY(EditAnywhere, Category="Path Finding")
	int32 TraceForWallsHeight = 100;

	// true = 8, false = 4
	UPROPERTY(EditAnywhere, Category="Path Finding")
	bool bDiagonalMovement = false;

	UPROPERTY(EditAnywhere, Category="Configs")
	TObjectPtr<UT3DConfigDataAsset> TilemapConfig;

	UPROPERTY()
	TArray<FT3DBlock> Block;

	UPROPERTY()
	TArray<FT3DPathFindingBlock> PathFindingBlocks;

	UPROPERTY()
	FT3DGameBoardData GameBoardData;

	UPROPERTY()
	FT3DPlayerStartLoc PlayerStartLoc;

	UPROPERTY(VisibleAnywhere, Category="Level Values")
	float PlayerStartHeight = 100.0f;

	UPROPERTY(VisibleAnywhere, Category="Level Values")
	float MapBoundOffset = 50.0f;

	int32 GetMaxLevelHeight() const { return (Floors + 1) * GridSize; }
	int32 GetMinLevelHeight() const { return 0; }
	int32 VectorToIndex(const int32 X, const int32 Y, const int32 Z) const;
	int32 VectorToIndex(const FVector& Location, int32 Floor) const;
	int32 VectorToIndex(const FVector& Location) const;
	int32 VectorToFloor(const FVector& Location) const;

	FVector IndexToVector(const int32 Index) const;

	const FT3DBlockConfig& GetBlockConfig(const FName& ID) const;
	const FT3DMeshConfig& GetMeshConfig(const FName& ID) const;
	int32 GetTerrainTextureIndex(const FName& ID, int32 Flag) const;
};
