#include "T3DTerrainGenerator.h"

#include <stdexcept>

#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Widgets/T3DEditorSceneViewportClient.h"
#include "Widgets/MapBuilder/T3DMapBuilderWidgetContext.h"

void FT3DTerrainGenerator::Setup(FT3DEditorSceneViewportClient* InViewport)
{
	UT3DAsset* Asset = InViewport->GetTilemapAsset();
	Asset->GameBoardData = {};

	GenerateMesh(InViewport);
	ApplyMesh(InViewport);
}

void FT3DTerrainGenerator::ModifyTerrainMesh(FT3DEditorSceneViewportClient* InViewport, const int32 InIndex, const FT3DBlockConfig& BlockConfig)
{
	UT3DAsset* Asset = InViewport->GetTilemapAsset();

	if (!Asset->Block.IsValidIndex(InIndex))
		return;
	
	Asset->Block[InIndex].BlockType = BlockConfig.BlockType;
	Asset->Block[InIndex].BlockID = BlockConfig.ID;
	Asset->Block[InIndex].BlockState = GBuilderWidgetContext.bHalfBlock.Get() ? ET3DBlockState::Half : ET3DBlockState::Full;
	Asset->GameBoardData = {};

	GenerateMesh(InViewport);
	ApplyMesh(InViewport);
}

void FT3DTerrainGenerator::GenerateMesh(FT3DEditorSceneViewportClient* InViewport)
{
	UT3DAsset* Asset = InViewport->GetTilemapAsset();

	for (int32 x = 0; x < Asset->LevelSizeX; ++x)
	{
		for (int32 y = 0; y < Asset->LevelSizeY; ++y)
		{
			for (int32 z = 0; z < Asset->Floors; ++z)
			{
				const int32 Index = Asset->VectorToIndex(x, y, z);
				if (Asset->Block[Index].BlockType != ET3DBlock::Air)
				{
					const FVector Location = FVector(x, y, z);

					for (const ET3DBlockDirection SurroundDir : { ET3DBlockDirection::Forward, ET3DBlockDirection::Right, ET3DBlockDirection::Back, ET3DBlockDirection::Left })
					{
						if (Asset->Block[Index].BlockState == ET3DBlockState::Full)
						{
							if (FullCheck(InViewport, GetLocationInDirection(SurroundDir, Location)))
							{
								CreateFace(InViewport, SurroundDir, Location * 100, Asset->Block[Index]);
							}
						}else if (Asset->Block[Index].BlockState == ET3DBlockState::Half)
						{
							if (HalfCheck(InViewport, GetLocationInDirection(SurroundDir, Location)))
							{
								CreateFace(InViewport, SurroundDir, Location * 100, Asset->Block[Index]);
							}
						}
					}

					for (const ET3DBlockDirection Dir : { ET3DBlockDirection::Up, ET3DBlockDirection::Down })
					{
						if (Check(InViewport, GetLocationInDirection(Dir, Location)))
						{
							CreateFace(InViewport, Dir, Location * 100, Asset->Block[Index]);
						}
					}
				}
			}
		}
	}
}

bool FT3DTerrainGenerator::FullCheck(FT3DEditorSceneViewportClient* InViewport, const FVector& Location)
{
	UT3DAsset* Asset = InViewport->GetTilemapAsset();

	if (Location.X >= Asset->LevelSizeX || Location.Y >= Asset->LevelSizeY || Location.X<0 || Location.Y<0 || Location.Z < 0)
		return true;
	if (Location.Z >= Asset->Floors)
		return true;

	const int32 Index = Asset->VectorToIndex(Location.X, Location.Y, Location.Z);
	
	if (Asset->Block[Index].BlockType == ET3DBlock::Air)
		return true;

	if (Asset->Block[Index].BlockType == ET3DBlock::Cube && Asset->Block[Index].BlockState == ET3DBlockState::Half)
		return true;

	return false;
}

bool FT3DTerrainGenerator::HalfCheck(FT3DEditorSceneViewportClient* InViewport, const FVector& Location)
{
	return Check(InViewport, Location);
}

bool FT3DTerrainGenerator::Check(FT3DEditorSceneViewportClient* InViewport, const FVector& Location)
{
	UT3DAsset* Asset = InViewport->GetTilemapAsset();
		
	if (Location.X >= Asset->LevelSizeX || Location.Y >= Asset->LevelSizeY || Location.X<0 || Location.Y<0 || Location.Z < 0)
		return true;
	if (Location.Z >= Asset->Floors)
		return true;
	
	return Asset->Block[Asset->VectorToIndex(Location.X, Location.Y, Location.Z)].BlockType == ET3DBlock::Air;
}

void FT3DTerrainGenerator::CreateFace(FT3DEditorSceneViewportClient* InViewport, const ET3DBlockDirection Direction,
                                      const FVector& Location, const FT3DBlock& InBlock)
{
	UT3DAsset* Asset = InViewport->GetTilemapAsset();
	
	const auto Normal = GetBlockNormal(Direction);
    const auto Color = FColor(0, 0, 0, GetBlockTextureIndex(InBlock.BlockID, Normal, InViewport));

    Asset->GameBoardData.Vertices.Append(GetBlockFaceVertices(InBlock.BlockState, Direction, Location));
    Asset->GameBoardData.Triangles.Append({
    	Asset->GameBoardData.VertexCount + 3, Asset->GameBoardData.VertexCount + 2,
    	Asset->GameBoardData.VertexCount, Asset->GameBoardData.VertexCount + 2,
    	Asset->GameBoardData.VertexCount + 1, Asset->GameBoardData.VertexCount
    });
    Asset->GameBoardData.Normals.Append({Normal, Normal, Normal, Normal});
    Asset->GameBoardData.Colors.Append({Color, Color, Color, Color});
    Asset->GameBoardData.UV0.Append({FVector2D(0, 0), FVector2D(1, 0), FVector2D(1, 1), FVector2D(0, 1)});

    Asset->GameBoardData.VertexCount += 4;
}

FVector FT3DTerrainGenerator::GetLocationInDirection(const ET3DBlockDirection Direction, const FVector& Location)
{
	switch (Direction)
	{
	case ET3DBlockDirection::Forward: return Location + FVector::ForwardVector;
	case ET3DBlockDirection::Back: return Location + FVector::BackwardVector;
	case ET3DBlockDirection::Left: return Location + FVector::LeftVector;
	case ET3DBlockDirection::Right: return Location + FVector::RightVector;
	case ET3DBlockDirection::Up: return Location + FVector::UpVector;
	case ET3DBlockDirection::Down: return Location + FVector::DownVector;
	default: throw std::invalid_argument("Invalid direction");
	}
}

FVector FT3DTerrainGenerator::GetBlockNormal(const ET3DBlockDirection Direction)
{
	switch (Direction)
	{
	case ET3DBlockDirection::Forward: return FVector::ForwardVector;
	case ET3DBlockDirection::Right: return FVector::RightVector;
	case ET3DBlockDirection::Back: return FVector::BackwardVector;
	case ET3DBlockDirection::Left: return FVector::LeftVector;
	case ET3DBlockDirection::Up: return FVector::UpVector;
	case ET3DBlockDirection::Down: return FVector::DownVector;
	default: throw std::invalid_argument("Invalid direction");
	}
}

int32 FT3DTerrainGenerator::GetBlockTextureIndex(const FName BlockID, const FVector& Normal,
	FT3DEditorSceneViewportClient* InViewport)
{
	UT3DAsset* Asset = InViewport->GetTilemapAsset();

	if (Normal == FVector::UpVector)
		return Asset->GetTerrainTextureIndex(BlockID, 0);
	if (Normal == FVector::DownVector)
		return Asset->GetTerrainTextureIndex(BlockID, 2);
	return Asset->GetTerrainTextureIndex(BlockID, 1);
}

TArray<FVector> FT3DTerrainGenerator::GetBlockFaceVertices(const ET3DBlockState BlockState, const ET3DBlockDirection Direction, const FVector& Location)
{
	TArray<FVector> Vertices;

	const FVector* BlockVertexData = BlockState == ET3DBlockState::Half ? HalfBlockVertexData : FullBlockVertexData;

	for (int i = 0; i < 4; i++)
	{
		Vertices.Add(BlockVertexData[BlockTriangleData[i + static_cast<int>(Direction) * 4]] + Location);
	}

	return Vertices;
}

void FT3DTerrainGenerator::ApplyMesh(FT3DEditorSceneViewportClient* InViewport)
{
	UT3DAsset* Asset = InViewport->GetTilemapAsset();
	UProceduralMeshComponent* TerrainMesh = InViewport->GetTerrainMesh();

	TerrainMesh->SetMaterial(0, GBuilderWidgetContext.DynamicTerrainMaterial);
	TerrainMesh->SetCollisionResponseToChannel(T3DTerrainPathTrace, ECR_Block);
	TerrainMesh->SetCollisionResponseToChannel(T3DTerrainEditorClickTrace, ECR_Block);
	TerrainMesh->CreateMeshSection(
		0,
		Asset->GameBoardData.Vertices,
		Asset->GameBoardData.Triangles,
		Asset->GameBoardData.Normals,
		Asset->GameBoardData.UV0,
		Asset->GameBoardData.Colors,
		TArray<FProcMeshTangent>(),
		true
	);
}
