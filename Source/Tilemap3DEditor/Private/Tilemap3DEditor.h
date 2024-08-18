#pragma once
class FT3DAssetTypeActions;

class FTilemap3DEditorModule final : public ITilemap3DEditorModule
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TSharedPtr<FT3DAssetTypeActions> T3DAssetTypeActions;
};
