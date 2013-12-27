#ifndef COMMANDMANAGER_H_
#define COMMANDMANAGER_H_

#include "Command.h"

#include <stack>
#include <gtest/gtest_prod.h>

using namespace std;

class CommandManager
{
private:
	FRIEND_TEST(CommandManagerTest, execute);
	FRIEND_TEST(CommandManagerTest, deleteRedoCommandsMemory);
	FRIEND_TEST(CommandManagerTest, deleteUndoCommandsMemory);
	FRIEND_TEST(CommandManagerTest, initial);

	stack<Command*> _redoCommands, _undoCommands;
	void deleteRedoCommandsMemory();
	void deleteUndoCommandsMemory();
public:
	CommandManager(void);
	~CommandManager(void);

	void execute(Command *command);
	bool redo();
	bool undo();

	void initial();
	bool canUndo();
	bool canRedo();
};

#endif