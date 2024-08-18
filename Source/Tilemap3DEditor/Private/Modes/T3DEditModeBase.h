#pragma once

class FT3DEditorSceneViewportClient;

class FT3DEditModeBase
{
public:
	explicit FT3DEditModeBase(const T3D::EMapBuilderMode InBuilderMode, const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient) : BuilderMode(InBuilderMode), ViewportClient(InViewportClient) {}
	T3D::EMapBuilderMode GetBuilderMode() const { return BuilderMode; }
	
	virtual void InputKey(const FInputKeyEventArgs& EventArgs) PURE_VIRTUAL(FT3DEditModeBase::InputKey, );
	virtual void Tick(float DeltaSeconds) PURE_VIRTUAL(FT3DEditModeBase::Tick, );

	virtual  ~FT3DEditModeBase() = default;

protected:
	T3D::EMapBuilderMode BuilderMode;
	TWeakPtr<FT3DEditorSceneViewportClient> ViewportClient;
};

class FT3DEditModeFactory
{
public:
	static FT3DEditModeBase* CreateEditMode(const T3D::EMapBuilderMode InBuilderMode, const TSharedPtr<FT3DEditorSceneViewportClient>& InViewportClient);
};