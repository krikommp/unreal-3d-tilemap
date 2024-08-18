#pragma once

class ST3DMapBuilderPlayerChessModeWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DMapBuilderPlayerChessModeWidget)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
private:
	TSharedPtr<SSegmentedControl<T3D::EMapBuilderPlayerPawnMode>> ModeSegmentedControl;
};
