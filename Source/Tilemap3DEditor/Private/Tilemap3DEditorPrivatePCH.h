#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "SEditorViewport.h"
#include "SCommonEditorViewportToolbarBase.h"
#include "AdvancedPreviewScene.h"
#include "SSingleObjectDetailsPanel.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Images/SImage.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SSegmentedControl.h"
#include "ISettingsModule.h"

#include "ITilemap3DEditorModule.h"
#include "T3DAsset.h"

#include "Widgets/MapBuilder/T3DMapBuilderMode.h"

#define TILEMAP_3D_MODULE TILEMAP_3D_EDITOR_MODULE
#define TILEMAP_3D_LOCTEXT_NAMESPACE TILEMAP_3D_MODULE

#define T3DTerrainEditorClickTrace ECC_GameTraceChannel1
#define T3DTerrainEditorMeshClickTrace ECC_GameTraceChannel2
#define T3DTerrainPathTrace ECC_GameTraceChannel3

DECLARE_LOG_CATEGORY_EXTERN(LogTilemap3DEditor, Log, All);

#define TILEMAP_3D_LOG_HELPER(VERBOSITY, TILEMAP3D_LOG_TEXT, ...)										\
do																										\
{																										\
UE_LOG( LogTilemap3DEditor, VERBOSITY, TILEMAP3D_LOG_TEXT, ##__VA_ARGS__ );								\
}																										\
while ( 0 )

#define TILEMAP_3D_LOG_MESSAGE( TILEMAP3D_LOG_TEXT, ... )												\
TILEMAP_3D_LOG_HELPER( Log, TILEMAP3D_LOG_TEXT, ##__VA_ARGS__ )

#define TILEMAP_3D_LOG_FATAL( TILEMAP3D_LOG_TEXT, ... )                                                  \
TILEMAP_3D_LOG_HELPER( Fatal, TILEMAP3D_LOG_TEXT, ##__VA_ARGS__ )

#define TILEMAP_3D_LOG_ERROR( TILEMAP3D_LOG_TEXT, ... )                                                  \
TILEMAP_3D_LOG_HELPER( Error, TILEMAP3D_LOG_TEXT, ##__VA_ARGS__ )

#define TILEMAP_3D_LOG_WARNING( TILEMAP3D_LOG_TEXT, ... )                                                \
TILEMAP_3D_LOG_HELPER( Warning, TILEMAP3D_LOG_TEXT, ##__VA_ARGS__ )

#define TILEMAP_3D_LOG_DISPLAY( TILEMAP3D_LOG_TEXT, ... )                                                \
TILEMAP_3D_LOG_HELPER( Display, TILEMAP3D_LOG_TEXT, ##__VA_ARGS__ )
