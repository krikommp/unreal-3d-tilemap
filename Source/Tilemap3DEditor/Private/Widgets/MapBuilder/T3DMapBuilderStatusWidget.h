#pragma once

class TILEMAP3DEDITOR_API ST3DMapBuilderStatusWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DMapBuilderStatusWidget)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
private:
	TSharedPtr<STextBlock> StatusText;
};
