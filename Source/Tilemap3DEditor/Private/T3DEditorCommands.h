#pragma once

#include "Framework/Commands/Commands.h"
#include "Styling/ISlateStyle.h"

class FT3DEditorCommands : public TCommands<FT3DEditorCommands>
{
public:
	FT3DEditorCommands()
		: TCommands<FT3DEditorCommands>(
			TEXT("T3DEditor"),
			NSLOCTEXT("Contexts", "T3DEditor", "T3DEditor"),
			NAME_None,
			FAppStyle::GetAppStyleSetName()
		)
	{
	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> UndoBuilderCommand;
};
