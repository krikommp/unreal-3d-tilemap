#pragma once

class FT3DEditorToolkit;

class ST3DPropertiesTabBody final : public SSingleObjectDetailsPanel
{
public:
	SLATE_BEGIN_ARGS(ST3DPropertiesTabBody)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TWeakObjectPtr<UT3DAsset> InAsset, TSharedPtr<FT3DEditorToolkit> InT3DEditor);
	//~ Begin SSingleObjectDetailsPanel interface
	virtual UObject* GetObjectToObserve() const override;
	virtual TSharedRef<SWidget> PopulateSlot(TSharedRef<SWidget> PropertyEditorWidget) override;
	//~ Begin SSingleObjectDetailsPanel interface

private:
	TWeakObjectPtr<UT3DAsset> T3DAsset;
	bool bCanEditProperty = true;
};
