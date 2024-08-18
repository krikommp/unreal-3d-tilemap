#pragma once

class TILEMAP3DEDITOR_API ST3DMapBuilderModeWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DMapBuilderModeWidget)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
private:
	TSharedPtr<SSegmentedControl<T3D::EMapBuilderMode>> ModeSegmentedControl;
};
