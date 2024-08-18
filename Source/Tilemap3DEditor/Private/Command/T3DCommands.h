#pragma once
#include "T3DCommand.h"

class FT3DEditorSceneViewportClient;

class FT3DAddCubeCommand final : public FT3DCommand
{
public:
	explicit FT3DAddCubeCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InIndex, const int32 InFloor);
	virtual void Execute() override;
	virtual void Undo() override;
	
private:
	int32 Index;
	int32 Floor;
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
};

class FT3DRemoveCubeCommand final : public FT3DCommand
{
public:
	explicit FT3DRemoveCubeCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InIndex, const int32 InFloor);
	virtual void Execute() override;
	virtual void Undo() override;
	
private:
	int32 Index;
	int32 Floor;
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
	FT3DBlockConfig BlockConfig;
	ET3DBlockState BlockState;
};

class FT3DCleanupPlayerStartCommand final : public FT3DCommand
{
public:
	explicit FT3DCleanupPlayerStartCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient);
	virtual void Execute() override;
	virtual void Undo() override;

private:
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
	int32 OldIndex = INDEX_NONE;
};

class FT3DCleanupPlayerPawnCommand final : public FT3DCommand
{
public:
	explicit FT3DCleanupPlayerPawnCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InIndex);
	virtual void Execute() override;
	virtual void Undo() override;

private:
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
	int32 OldIndex = INDEX_NONE;
};

class FT3DSpawnPlayerPawnCommand final : public FT3DCommand
{
public:
	explicit FT3DSpawnPlayerPawnCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InIndex);
	virtual void Execute() override;
	virtual void Undo() override;
	
private:
	int32 Index;
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
};

class FT3DRemovePlayerPawnCommand final : public FT3DCommand
{
public:
	explicit FT3DRemovePlayerPawnCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InIndex);
	virtual void Execute() override;
	virtual void Undo() override;
	
private:
	int32 Index;
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
};

class FT3DSpawnPlayerStartCommand final : public FT3DCommand
{
public:
	explicit FT3DSpawnPlayerStartCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InIndex);
	virtual void Execute() override;
	virtual void Undo() override;
	
private:
	int32 Index;
	int32 OldIndex;
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
};

class FT3DFillCommand final : public FT3DCommand
{
public:
	explicit FT3DFillCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InFloor);
	virtual void Execute() override;
	virtual void Undo() override;
	
private:
	int32 Floor;
	TArray<int32> ModifiedIndices;
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
};

class FT3DSpawnMeshCommand final : public FT3DCommand
{
public:
	explicit FT3DSpawnMeshCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const FT3DMeshConfig& InMeshConfig, const int32 InIndex);
	virtual void Execute() override;
	virtual void Undo() override;
	
private:
	int32 Index;
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
	FT3DMeshConfig MeshConfig;
};

class FT3DRemoveMeshCommand final : public FT3DCommand
{
public:
	explicit FT3DRemoveMeshCommand(const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient, const int32 InIndex);
	virtual void Execute() override;
	virtual void Undo() override;

private:
	int32 Index;
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
	FT3DMeshConfig MeshConfig;	
};

class FT3DModifyMeshScaleX final : public FT3DCommand
{
public:
	explicit FT3DModifyMeshScaleX(const TWeakObjectPtr<UT3DAsset>& InAsset, const int32 InIndex, const float InValue);
	virtual void Execute() override;
	virtual void Undo() override;

private:
	int32 Index;
	float NewValue;
	float OldValue;
	TWeakObjectPtr<UT3DAsset> Asset;
};

class FT3DModifyMeshScaleY final : public FT3DCommand
{
public:
	explicit FT3DModifyMeshScaleY(const TWeakObjectPtr<UT3DAsset>& InAsset, const int32 InIndex, const float InValue);
	virtual void Execute() override;
	virtual void Undo() override;

private:
	int32 Index;
	float NewValue;
	float OldValue;
	TWeakObjectPtr<UT3DAsset> Asset;
};

class FT3DModifyMeshScaleZ final : public FT3DCommand
{
public:
	explicit FT3DModifyMeshScaleZ(const TWeakObjectPtr<UT3DAsset>& InAsset, const int32 InIndex, const float InValue);
	virtual void Execute() override;
	virtual void Undo() override;

private:
	int32 Index;
	float NewValue;
	float OldValue;
	TWeakObjectPtr<UT3DAsset> Asset;
};

class FT3DModifyMeshRotatorYaw final : public FT3DCommand
{
public:
	explicit FT3DModifyMeshRotatorYaw(const TWeakObjectPtr<UT3DAsset>& InAsset, const int32 InIndex, const float InValue);
	virtual void Execute() override;
	virtual void Undo() override;

private:
	int32 Index;
	float NewValue;
	float OldValue;
	TWeakObjectPtr<UT3DAsset> Asset;
};

class FT3DModifyMeshRotatorPitch final : public FT3DCommand
{
public:
	explicit FT3DModifyMeshRotatorPitch(const TWeakObjectPtr<UT3DAsset>& InAsset, const int32 InIndex, const float InValue);
	virtual void Execute() override;
	virtual void Undo() override;

private:
	int32 Index;
	float NewValue;
	float OldValue;
	TWeakObjectPtr<UT3DAsset> Asset;
};

class FT3DModifyMeshRotatorRoll final : public FT3DCommand
{
public:
	explicit FT3DModifyMeshRotatorRoll(const TWeakObjectPtr<UT3DAsset>& InAsset, const int32 InIndex, const float InValue);
	virtual void Execute() override;
	virtual void Undo() override;

private:
	int32 Index;
	float NewValue;
	float OldValue;
	TWeakObjectPtr<UT3DAsset> Asset;
};