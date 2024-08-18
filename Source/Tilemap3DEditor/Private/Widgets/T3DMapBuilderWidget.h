#pragma once

class ST3DMapBuilderWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ST3DMapBuilderWidget)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TWeakObjectPtr<UT3DAsset> InAsset);

private:
	TWeakObjectPtr<UT3DAsset> T3DAsset;
};
