#include "gtest\gtest.h"
#include "CommandManager.h"
#include "Command.h"
#include "ActivityDiagram.h"
#include "Glyph.h"

class CommandManagerTest :
	public testing::Test
{
protected:
	CommandManager _commandManager;
	ActivityDiagram _activityDiagram;
	Command *_command0, *_command1, *_command2;
	virtual void SetUp()
	{
		// command 會在 commandManager 內被 delete ， 故不在此 new
	}

	virtual void TearDown()
	{
		// command 會在 commandManager 內被 delete
	}
};

TEST_F(CommandManagerTest, execute)
{
	_command0 = new AddGlyphCommand(&_activityDiagram, 0, ACTIVITY, "A0");
	_command1 = new AddGlyphCommand(&_activityDiagram, 1, ACTIVITY, "A1");
	_command2 = new AddGlyphCommand(&_activityDiagram, 2, ACTIVITY, "A2");

	_commandManager.execute(_command0);
	_commandManager.execute(_command1);
	_commandManager.execute(_command2);
	EXPECT_EQ(_commandManager._undoCommands.size(), 3);
	_commandManager.deleteUndoCommandsMemory();
}

TEST_F(CommandManagerTest, redo)
{
	_command0 = new AddGlyphCommand(&_activityDiagram, 0, ACTIVITY, "A0");
	_command1 = new AddGlyphCommand(&_activityDiagram, 1, ACTIVITY, "A1");
	_command2 = new AddGlyphCommand(&_activityDiagram, 2, ACTIVITY, "A2");

	EXPECT_FALSE(_commandManager.redo());
	_commandManager.execute(_command0);
	_commandManager.execute(_command1);
	_commandManager.execute(_command2);
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.redo());
	EXPECT_TRUE(_commandManager.redo());
	EXPECT_TRUE(_commandManager.redo());
	EXPECT_FALSE(_commandManager.redo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.redo());
	EXPECT_TRUE(_commandManager.redo());
	EXPECT_TRUE(_commandManager.redo());
	EXPECT_FALSE(_commandManager.redo());
}

TEST_F(CommandManagerTest, undo)
{
	_command0 = new AddGlyphCommand(&_activityDiagram, 0, ACTIVITY, "A0");
	_command1 = new AddGlyphCommand(&_activityDiagram, 1, ACTIVITY, "A1");
	_command2 = new AddGlyphCommand(&_activityDiagram, 2, ACTIVITY, "A2");

	EXPECT_FALSE(_commandManager.undo());
	_commandManager.execute(_command0);
	_commandManager.execute(_command1);
	_commandManager.execute(_command2);
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_FALSE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.redo());
	EXPECT_TRUE(_commandManager.redo());
	EXPECT_TRUE(_commandManager.redo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_FALSE(_commandManager.undo());
}

TEST_F(CommandManagerTest, deleteRedoCommandsMemory)
{
	_command0 = new AddGlyphCommand(&_activityDiagram, 0, ACTIVITY, "A0");
	_command1 = new AddGlyphCommand(&_activityDiagram, 1, ACTIVITY, "A1");
	_command2 = new AddGlyphCommand(&_activityDiagram, 2, ACTIVITY, "A2");

	EXPECT_EQ(_commandManager._redoCommands.size(), 0);
	_commandManager.execute(_command0);
	_commandManager.execute(_command1);
	_commandManager.execute(_command2);
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_EQ(_commandManager._redoCommands.size(), 3);
	_commandManager.deleteRedoCommandsMemory();
	EXPECT_EQ(_commandManager._redoCommands.size(), 0);
}

TEST_F(CommandManagerTest, deleteUndoCommandsMemory)
{
	_command0 = new AddGlyphCommand(&_activityDiagram, 0, ACTIVITY, "A0");
	_command1 = new AddGlyphCommand(&_activityDiagram, 1, ACTIVITY, "A1");
	_command2 = new AddGlyphCommand(&_activityDiagram, 2, ACTIVITY, "A2");

	EXPECT_EQ(_commandManager._undoCommands.size(), 0);
	_commandManager.execute(_command0);
	_commandManager.execute(_command1);
	_commandManager.execute(_command2);
	EXPECT_EQ(_commandManager._undoCommands.size(), 3);
	_commandManager.deleteUndoCommandsMemory();
	EXPECT_EQ(_commandManager._undoCommands.size(), 0);
}

TEST_F(CommandManagerTest, initial)
{
	_command0 = new AddGlyphCommand(&_activityDiagram, 0, ACTIVITY, "A0");
	_command1 = new AddGlyphCommand(&_activityDiagram, 1, ACTIVITY, "A1");
	_command2 = new AddGlyphCommand(&_activityDiagram, 2, ACTIVITY, "A2");

	EXPECT_EQ(_commandManager._undoCommands.size(), 0);
	EXPECT_EQ(_commandManager._redoCommands.size(), 0);
	_commandManager.execute(_command0);
	_commandManager.execute(_command1);
	_commandManager.execute(_command2);
	EXPECT_EQ(_commandManager._undoCommands.size(), 3);
	EXPECT_TRUE(_commandManager.undo());
	EXPECT_EQ(_commandManager._undoCommands.size(), 2);
	EXPECT_EQ(_commandManager._redoCommands.size(), 1);
	_commandManager.initial();
	EXPECT_EQ(_commandManager._undoCommands.size(), 0);
	EXPECT_EQ(_commandManager._redoCommands.size(), 0);
}