#include "T3DAsset.h"

#include "Engine/DataAsset.h"
#include "Engine/Texture2DArray.h"
#include "Engine/DataTable.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(T3DAsset)

FT3DBlockConfig FT3DBlockConfig::EmptyBlock;
FT3DMeshConfig FT3DMeshConfig::EmptyBlock;

int32 UT3DAsset::VectorToIndex(const int32 X, const int32 Y, const int32 Z) const
{
	return Z * LevelSizeX * LevelSizeY + Y * LevelSizeX + X; 
}

int32 UT3DAsset::VectorToIndex(const FVector& Location, int32 Floor) const
{
	const float PivotX = (GridSize * 0.5) + Location.X;
	const float PivotY = (GridSize * 0.5) + Location.Y;

	const float ModX = FMath::Floor(FMath::Fmod(PivotX, GridSize));
	const float ModY = FMath::Floor(FMath::Fmod(PivotY, GridSize));

	const int AddX = ModX ? 1 : 0;
	const int AddY = ModY ? 1 : 0;

	const int X = FMath::Floor(((PivotX + AddX)) / GridSize);
	const int Y = FMath::Floor(((PivotY + AddY)) / GridSize) *
		LevelSizeX;

	const int32 Result = X + Y;

	return Result + LevelSizeX * LevelSizeY * Floor;
}

int32 UT3DAsset::VectorToIndex(const FVector& Location) const
{
	const int32 Floor = VectorToFloor(Location);
	return VectorToIndex(Location, Floor);
}

int32 UT3DAsset::VectorToFloor(const FVector& Location) const
{
	return FMath::Floor(Location.Z / GridSize);
}

FVector UT3DAsset::IndexToVector(const int32 Index) const
{
	const int32 ResidueX = Index % LevelSizeX;
	const float X = GridSize * ResidueX;

	const int32 ResidueYZ = Index / LevelSizeX;
	const int32 SquaredXY = LevelSizeX * LevelSizeY;
	const int32 ResidueZ = Index / SquaredXY;
	const int32 ResidueXZ = LevelSizeX * ResidueZ;
	const int32 ResidueY = ResidueYZ - ResidueXZ;
	const float Y = ResidueY * GridSize;

	const float Z = ResidueZ * GridSize;

	return FVector(X, Y, Z);
}

const FT3DBlockConfig& UT3DAsset::GetBlockConfig(const FName& ID) const
{
	for (const auto& BlockConfig : TilemapConfig->BlockConfigs)
	{
		if (BlockConfig.ID == ID)
		{
			return BlockConfig;
		}
	}
	return FT3DBlockConfig::EmptyBlock;
}

const FT3DMeshConfig& UT3DAsset::GetMeshConfig(const FName& ID) const
{
	for (const auto& BlockConfig : TilemapConfig->MeshConfigs)
	{
		if (BlockConfig.ID == ID)
		{
			return BlockConfig;
		}
	}
	return FT3DMeshConfig::EmptyBlock;
}

int32 UT3DAsset::GetTerrainTextureIndex(const FName& ID, int32 Flag) const
{
	UTexture2D* Tex = nullptr;
	for (const auto& BlockConfig : TilemapConfig->BlockConfigs)
	{
		if (BlockConfig.ID == ID)
		{
			if (BlockConfig.BlockTextures.Num() <= Flag)
			{
				Tex = BlockConfig.BlockTextures.Last();
			}else
			{
				Tex = BlockConfig.BlockTextures[Flag];
			}
			break;
		}
	}

	if (Tex == nullptr)
		return INDEX_NONE;

	for (int32 SourceIndex = 0; SourceIndex < TilemapConfig->Textures->SourceTextures.Num(); ++SourceIndex)
	{
		if (TilemapConfig->Textures->SourceTextures[SourceIndex] == Tex)
			return SourceIndex;
	}

	return INDEX_NONE;
}
