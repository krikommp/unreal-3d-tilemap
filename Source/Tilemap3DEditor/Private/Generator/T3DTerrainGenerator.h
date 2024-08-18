#pragma once

class UT3DAsset;
class FT3DEditorSceneViewportClient;

class FT3DTerrainGenerator
{
public:
	static void Setup(FT3DEditorSceneViewportClient* InViewport);
	static void ModifyTerrainMesh(FT3DEditorSceneViewportClient* InViewport, const int32 InIndex, const FT3DBlockConfig& BlockConfig);

private:
	static void GenerateMesh(FT3DEditorSceneViewportClient* InViewport);
	static bool FullCheck(FT3DEditorSceneViewportClient* InViewport, const FVector& Location);
	static bool HalfCheck(FT3DEditorSceneViewportClient* InViewport, const FVector& Location);
	static bool Check(FT3DEditorSceneViewportClient* InViewport, const FVector& Location);
	static void CreateFace(FT3DEditorSceneViewportClient* InViewport, const ET3DBlockDirection Direction, const FVector& Location, const FT3DBlock& InBlock);
	static FVector GetLocationInDirection(const ET3DBlockDirection Direction, const FVector& Position);
	static FVector GetBlockNormal(const ET3DBlockDirection Direction);
	static int32 GetBlockTextureIndex(const FName BlockID, const FVector& Normal, FT3DEditorSceneViewportClient* InViewport);
	static TArray<FVector> GetBlockFaceVertices(const ET3DBlockState BlockState, const ET3DBlockDirection Direction, const FVector& Location);
	static void ApplyMesh(FT3DEditorSceneViewportClient* InViewport);


	inline static const FVector FullBlockVertexData[8] = {
		FVector(50, 50, 100),
		FVector(50, -50, 100),
		FVector(50, -50, 0),
		FVector(50, 50, 0),
		FVector(-50, -50, 100),
		FVector(-50, 50, 100),
		FVector(-50, 50, 0),
		FVector(-50, -50, 0)
	};
	
	inline static const FVector HalfBlockVertexData[8] = {
    		FVector(50, 50, 50),
    		FVector(50, -50, 50),
    		FVector(50, -50, 0),
    		FVector(50, 50, 0),
    		FVector(-50, -50, 50),
    		FVector(-50, 50,  50),
    		FVector(-50, 50, 0),
    		FVector(-50, -50, 0)
	};

	inline static const int BlockTriangleData[24] = {
		0, 1, 2, 3, // Forward
		5, 0, 3, 6, // Right
		4, 5, 6, 7, // Back
		1, 4, 7, 2, // Left
		5, 4, 1, 0, // Up
		3, 2, 7, 6 // Down
	};
};
