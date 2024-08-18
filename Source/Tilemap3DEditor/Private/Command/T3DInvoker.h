#pragma once

#include "T3DCommand.h"
#define MAX_COMMAND_STACK_SIZE 100

class FT3DInvoker
{
	bool CheckCommandFullFilled() const;
public:
	void Execute(FT3DCommand* InCommand);
	void UndoLastCommand();
	
private:
	TArray<TUniquePtr<FT3DCommand>> CommandStack;
};
