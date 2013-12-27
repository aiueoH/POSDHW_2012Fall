#include "CommandManager.h"

CommandManager::CommandManager(void)
{
}

CommandManager::~CommandManager(void)
{
	deleteRedoCommandsMemory();
	deleteUndoCommandsMemory();
}

void CommandManager::execute(Command *command)
{
	command->execute();
	_undoCommands.push(command);
	deleteRedoCommandsMemory();
}

bool CommandManager::redo()
{
	if (!_redoCommands.empty())
	{
		Command *command = _redoCommands.top();
		command->execute();
		_redoCommands.pop();
		_undoCommands.push(command);
		return true;
	}
	return false;
}

bool CommandManager::undo()
{
	if (!_undoCommands.empty())
	{
		Command *command = _undoCommands.top();
		command->unexecute();
		_undoCommands.pop();
		_redoCommands.push(command);
		return true;
	}
	return false;
}

void CommandManager::deleteRedoCommandsMemory()
{
	while (!_redoCommands.empty())
	{
		delete _redoCommands.top();
		_redoCommands.pop();
	}
}

void CommandManager::deleteUndoCommandsMemory()
{
	while (!_undoCommands.empty())
	{
		delete _undoCommands.top();
		_undoCommands.pop();
	}
}

void CommandManager::initial()
{
	deleteRedoCommandsMemory();
	deleteUndoCommandsMemory();
}

bool CommandManager::canRedo()
{
	if (_redoCommands.empty())
		return false;
	else
		return true;
}

bool CommandManager::canUndo()
{
	if (_undoCommands.empty())
		return false;
	else
		return true;
}