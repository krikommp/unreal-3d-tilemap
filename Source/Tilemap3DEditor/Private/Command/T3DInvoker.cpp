#include "T3DInvoker.h"

bool FT3DInvoker::CheckCommandFullFilled() const
{
	return CommandStack.Num() < MAX_COMMAND_STACK_SIZE;
}

void FT3DInvoker::Execute(FT3DCommand* InCommand)
{
	if (!CheckCommandFullFilled())
	{
		TILEMAP_3D_LOG_WARNING(TEXT("Command stack is full, removing the oldest command."));
		CommandStack.RemoveAt(0);
	}
	TUniquePtr<FT3DCommand> Command(InCommand);
	Command->Execute();
	CommandStack.Add(MoveTemp(Command));
}

void FT3DInvoker::UndoLastCommand()
{
	if (CommandStack.Num() > 0)
	{
		CommandStack.Last()->Undo();
		CommandStack.Pop();
	}
}
