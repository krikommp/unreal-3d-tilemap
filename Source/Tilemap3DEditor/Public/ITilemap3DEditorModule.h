#pragma once

#include "Modules/ModuleManager.h"

#define TILEMAP_3D_EDITOR_MODULE "Tilemap3DEditor"

class ITilemap3DEditorModule : public IModuleInterface
{
public:
	static ITilemap3DEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ITilemap3DEditorModule>(TILEMAP_3D_EDITOR_MODULE);
	}

	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded(TILEMAP_3D_EDITOR_MODULE);
	}
};
 