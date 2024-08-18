#include "T3DEditorCommands.h"

#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

void FT3DEditorCommands::RegisterCommands()
{
	UI_COMMAND(UndoBuilderCommand, "Undo Builder", "Undo Builder", EUserInterfaceActionType::Button, FInputChord(EKeys::Z, EModifierKey::Control));
}


#undef LOCTEXT_NAMESPACE