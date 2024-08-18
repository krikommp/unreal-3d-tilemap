﻿#pragma once
#include "T3DEditModeBase.h"

class FT3DPlayerPawnMode final : public FT3DEditModeBase
{
public:
	explicit FT3DPlayerPawnMode(T3D::EMapBuilderMode InBuilderMode, const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient)
		: FT3DEditModeBase(InBuilderMode, InViewportClient)
	{
	}

	virtual void InputKey(const FInputKeyEventArgs& EventArgs) override;
	virtual void Tick(float DeltaSeconds) override;
};