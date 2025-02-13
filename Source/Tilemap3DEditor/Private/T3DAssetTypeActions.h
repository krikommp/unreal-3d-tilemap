﻿#pragma once
#include "AssetTypeActions_Base.h"

class FT3DAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FT3DAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);

	//~ Begin IAssetTypeActions interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects,
	                             TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	virtual uint32 GetCategories() override;
	//~ Begin IAssetTypeActions interface

private:
	EAssetTypeCategories::Type MyAssetCategory;
};
