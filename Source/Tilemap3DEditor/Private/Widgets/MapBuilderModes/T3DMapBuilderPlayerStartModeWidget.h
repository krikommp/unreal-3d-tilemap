#pragma once

class ST3DMapBuilderPlayerStartModeWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DMapBuilderPlayerStartModeWidget)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
private:
	TSharedPtr<SSegmentedControl<T3D::EMapBuilderPlayerStartMode>> ModeSegmentedControl;
};
