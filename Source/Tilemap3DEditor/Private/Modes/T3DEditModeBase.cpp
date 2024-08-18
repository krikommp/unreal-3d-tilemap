#include "T3DEditModeBase.h"

#include "FT3DBlockEditMode.h"
#include "T3DMeshMode.h"
#include "T3DPlayerPawnMode.h"
#include "T3DPlayerStartMode.h"
#include "Widgets/T3DEditorSceneViewportClient.h"

FT3DEditModeBase* FT3DEditModeFactory::CreateEditMode(const T3D::EMapBuilderMode InBuilderMode, const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient)
{
	if (InBuilderMode == T3D::EMapBuilderMode::Block)
	{
		return new FT3DBlockEditMode(InBuilderMode, InViewportClient);
	}
	if (InBuilderMode == T3D::EMapBuilderMode::PlayerStart)
	{
		return new FT3DPlayerStartMode(InBuilderMode, InViewportClient);
	}
	if (InBuilderMode == T3D::EMapBuilderMode::PlayerPawn)
	{
		return new FT3DPlayerPawnMode(InBuilderMode, InViewportClient);
	}
	if (InBuilderMode == T3D::EMapBuilderMode::Mesh)
	{
		return new FT3DMeshMode(InBuilderMode, InViewportClient);
	}
	return nullptr;
}