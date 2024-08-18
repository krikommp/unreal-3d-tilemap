#pragma once

class FT3DCommand
{
public:
	virtual void Execute() PURE_VIRTUAL(FT3DCommand::Execute, );
	virtual void Undo() PURE_VIRTUAL(FT3DCommand::Undo, );
	
	virtual ~FT3DCommand() = default;
};
