#include "gtest\gtest.h"
#include "ActivityDiagram.h"
#include "Activity.h"
#include "Edge.h"
#include "Glyph.h"
#include "Globle.h"

class ActivityDiagramTest :
	public testing::Test
{
protected:
	ActivityDiagram _activityDiagram;
	Glyph *_decisionNode0, *_decisionNode1, *_decisionNode2, 
		*_initialNode0,
		*_finalNode0,
		*_edge0, *_edge1, *_edge2;

	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(ActivityDiagramTest, connectGlyph)
{
	_decisionNode0 = _activityDiagram.addGlyph(0, DECISION_NODE, "");
	_decisionNode0 = _activityDiagram.addGlyph(1, DECISION_NODE, "");
	_edge0 = _activityDiagram.addGlyph(2, EDGE, "E0");
	_edge1 = _activityDiagram.addGlyph(3, EDGE, "E1");
	EXPECT_FALSE(_activityDiagram.connectGlyph(0, 1));
	EXPECT_TRUE(_activityDiagram.connectGlyph(0, 2));
}

TEST_F(ActivityDiagramTest, isExistPathBetween)
{
	_decisionNode0 = _activityDiagram.addGlyph(0, DECISION_NODE, "");
	_edge0 = _activityDiagram.addGlyph(1, EDGE, "E0");
	EXPECT_FALSE(_activityDiagram.isExistPathBetween(0, 1));
	EXPECT_TRUE(_activityDiagram.connectGlyph(0, 1));
	EXPECT_TRUE(_activityDiagram.isExistPathBetween(0, 1));
}

TEST_F(ActivityDiagramTest, deleteGlyph)
{
	_decisionNode0 = _activityDiagram.addGlyph(0, DECISION_NODE, "");
	_edge0 = _activityDiagram.addGlyph(1, EDGE, "E0");
	_edge1 = _activityDiagram.addGlyph(2, EDGE, "E1");
	EXPECT_TRUE(_activityDiagram.connectGlyph(1, 0));
	EXPECT_TRUE(_activityDiagram.connectGlyph(0, 2));
	EXPECT_TRUE(_activityDiagram.deleteGlyph(0));
}

TEST_F(ActivityDiagramTest, deleteConnection)
{
	_decisionNode0 = _activityDiagram.addGlyph(0, DECISION_NODE, "");
	_edge0 = _activityDiagram.addGlyph(1, EDGE, "E0");
	EXPECT_TRUE(_activityDiagram.connectGlyph(0, 1));
	EXPECT_TRUE(_activityDiagram.deleteConnection(0, 1));
}

TEST_F(ActivityDiagramTest, getGlyphById)
{
	_decisionNode0 = _activityDiagram.addGlyph(0, DECISION_NODE, "");
	EXPECT_TRUE(_activityDiagram.getGlyphById(0) != NULL);
	EXPECT_TRUE(_activityDiagram.getGlyphById(1) == NULL);
}

TEST_F(ActivityDiagramTest, visitGlyphs)
{
	_decisionNode0 = _activityDiagram.addGlyph(0, DECISION_NODE, "");
	_decisionNode1 = _activityDiagram.addGlyph(1, DECISION_NODE, "");
	_decisionNode2 = _activityDiagram.addGlyph(2, DECISION_NODE, "");
	_edge0 = _activityDiagram.addGlyph(3, EDGE, "E0");
	_edge1 = _activityDiagram.addGlyph(4, EDGE, "E1");
	_edge2 = _activityDiagram.addGlyph(5, EDGE, "E2");
	EXPECT_TRUE(_activityDiagram.connectGlyph(0, 3));
	EXPECT_TRUE(_activityDiagram.connectGlyph(3, 1));
	EXPECT_TRUE(_activityDiagram.connectGlyph(1, 4));
	EXPECT_TRUE(_activityDiagram.connectGlyph(4, 0));
	EXPECT_TRUE(_activityDiagram.connectGlyph(1, 5));
	EXPECT_TRUE(_activityDiagram.connectGlyph(5, 2));
	vector<Glyph*> visitedGlyphs;
	EXPECT_TRUE(_activityDiagram.visitGlyphs(_decisionNode0, _decisionNode0, &visitedGlyphs));
	visitedGlyphs.clear();
	EXPECT_TRUE(_activityDiagram.visitGlyphs(_decisionNode1, _decisionNode0, &visitedGlyphs));
	visitedGlyphs.clear();
	EXPECT_TRUE(_activityDiagram.visitGlyphs(_decisionNode2, _decisionNode0, &visitedGlyphs));
	visitedGlyphs.clear();
	EXPECT_TRUE(_activityDiagram.visitGlyphs(_edge0, _decisionNode0, &visitedGlyphs));
	visitedGlyphs.clear();
	EXPECT_TRUE(_activityDiagram.visitGlyphs(_edge1, _decisionNode0, &visitedGlyphs));
	visitedGlyphs.clear();
	EXPECT_TRUE(_activityDiagram.visitGlyphs(_edge2, _decisionNode0, &visitedGlyphs));
	visitedGlyphs.clear();
	EXPECT_FALSE(_activityDiagram.visitGlyphs(_edge1, _edge2, &visitedGlyphs));
}

TEST_F(ActivityDiagramTest, isVisited)
{
	_decisionNode0 = _activityDiagram.addGlyph(0, DECISION_NODE, "");
	vector<Glyph*> visitedGlyphs;
	EXPECT_FALSE(_activityDiagram.isVisited(_decisionNode0, &visitedGlyphs));
	visitedGlyphs.push_back(_decisionNode0);
	EXPECT_TRUE(_activityDiagram.isVisited(_decisionNode0, &visitedGlyphs));
}

TEST_F(ActivityDiagramTest, deleteGlyphsMemory)
{
	EXPECT_EQ(_activityDiagram._glyphs.size(), 0);
	_decisionNode0 = _activityDiagram.addGlyph(0, DECISION_NODE, "");
	EXPECT_EQ(_activityDiagram._glyphs.size(), 1);
	_activityDiagram.deleteGlyphsMemory();
	EXPECT_EQ(_activityDiagram._glyphs.size(), 0);
}

TEST_F(ActivityDiagramTest, addGlyphCommand)
{
	int idCount_decisionNode = _activityDiagram._idCount;
	int id_decisionNode = _activityDiagram.addGlyphCommand("D");
	EXPECT_EQ(id_decisionNode, idCount_decisionNode);
	int idCount_edge = _activityDiagram._idCount;
	int id_edge = _activityDiagram.addGlyphCommand("E, edge!");
	EXPECT_EQ(id_edge, idCount_edge);
}

TEST_F(ActivityDiagramTest, connectGlyphCommand_int_int)
{
	int id_decisionNode = _activityDiagram.addGlyphCommand(DECISION_NODE, "");
	int id_edge = _activityDiagram.addGlyphCommand(EDGE, "edge!");
	EXPECT_EQ(_activityDiagram.connectGlyphCommand(id_decisionNode, id_decisionNode), ActivityDiagram::CONNECT_ITSELF);
	EXPECT_EQ(_activityDiagram.connectGlyphCommand(id_decisionNode, id_edge), ActivityDiagram::SUCCESS);
}

TEST_F(ActivityDiagramTest, connectGlyphCommand_string)
{
	_activityDiagram.addGlyphCommand(DECISION_NODE, "");
	_activityDiagram.addGlyphCommand(EDGE, "edge!");
	EXPECT_EQ(_activityDiagram.connectGlyphCommand("0,0"), ActivityDiagram::CONNECT_ITSELF);
	EXPECT_EQ(_activityDiagram.connectGlyphCommand("0,1"), ActivityDiagram::SUCCESS);
}

TEST_F(ActivityDiagramTest, deleteGlyphCommand)
{
	int id_decisionNode = _activityDiagram.addGlyphCommand(DECISION_NODE, "");
	EXPECT_TRUE(_activityDiagram.deleteGlyphCommand(id_decisionNode));
	EXPECT_FALSE(_activityDiagram.deleteGlyphCommand(id_decisionNode));
}

TEST_F(ActivityDiagramTest, canConnectGlyph)
{
	int id_decisionNode = _activityDiagram.addGlyphCommand(DECISION_NODE, "");
	int id_edge = _activityDiagram.addGlyphCommand(EDGE, "edge!");
	int id_initialNode = _activityDiagram.addGlyphCommand(INITIAL_NODE, "");
	int id_finalNode = _activityDiagram.addGlyphCommand(FINAL_NODE, "");
	EXPECT_EQ(_activityDiagram.canConnectGlyph(id_decisionNode, id_decisionNode), ActivityDiagram::CONNECT_ITSELF);
	EXPECT_EQ(_activityDiagram.canConnectGlyph(id_edge, id_initialNode), ActivityDiagram::CANNOT_BE_CONNECTED);
	EXPECT_EQ(_activityDiagram.canConnectGlyph(id_finalNode, id_edge), ActivityDiagram::CANNOT_CONNECT);
	EXPECT_EQ(_activityDiagram.canConnectGlyph(id_decisionNode, id_finalNode), ActivityDiagram::OTHER_ERROR);
	EXPECT_EQ(_activityDiagram.canConnectGlyph(id_edge, id_finalNode), ActivityDiagram::SUCCESS);
}

TEST_F(ActivityDiagramTest, getGlyphIndex)
{
	int id_decisionNode = INDEX_OF_NOT_FOUND;
	EXPECT_EQ(_activityDiagram.getGlyphIndex(id_decisionNode), INDEX_OF_NOT_FOUND);
	id_decisionNode = _activityDiagram.addGlyphCommand(DECISION_NODE, "");
	EXPECT_EQ(_activityDiagram.getGlyphIndex(id_decisionNode), 0);
}

TEST_F(ActivityDiagramTest, isConnected)
{
	int id_decisionNode = _activityDiagram.addGlyphCommand(DECISION_NODE, "");
	int id_edge = _activityDiagram.addGlyphCommand(EDGE, "edge!");
	EXPECT_FALSE(_activityDiagram.isConnected(id_decisionNode, id_edge));
	EXPECT_TRUE(_activityDiagram.connectGlyph(id_decisionNode, id_edge));
	EXPECT_TRUE(_activityDiagram.isConnected(id_decisionNode, id_edge));
}

// Integration testing ----------------------------------------------------

TEST_F(ActivityDiagramTest, testLoadFileNotExist)
{
	EXPECT_TRUE(_activityDiagram.loadActivityDiagramFile("testdata/test_file1.add"));
	EXPECT_FALSE(_activityDiagram.loadActivityDiagramFile("testdata/file_not_exist.add")); // Assert file not found error
}

TEST_F(ActivityDiagramTest, testIsPathExisBetweenGlyphs)
{
	EXPECT_TRUE(_activityDiagram.loadActivityDiagramFile("testdata/test_file1.add")); // Assert the diagram is loaded correctly 
	EXPECT_TRUE(_activityDiagram.isExistPathBetween(0, 8)); // Assert there exists a path 
	EXPECT_FALSE(_activityDiagram.isExistPathBetween(6, 10)); // Assert there is no path
}

TEST_F(ActivityDiagramTest, testUndoDeleteGlyph)
{
	EXPECT_TRUE(_activityDiagram.loadActivityDiagramFile("testdata/test_file1.add")); // Assert the diagram is loaded correctly 
	int idCount = _activityDiagram._idCount;
	int id = _activityDiagram.addGlyphCommand(EDGE, "Test");
	EXPECT_EQ(id, idCount); // Assert the edge is added correctly
	EXPECT_TRUE(_activityDiagram.deleteGlyphCommand(id)); 
	EXPECT_TRUE(_activityDiagram.getGlyphById(id) == NULL); // Assert the edge has been deleted
	EXPECT_TRUE(_activityDiagram.undo());
	EXPECT_EQ(_activityDiagram.getGlyphById(id)->getText(), "Test"); // Assert there is an edge with text ¡§Test¡¨
}

TEST_F(ActivityDiagramTest, testRedoConnectGlyphs)
{
	EXPECT_TRUE(_activityDiagram.loadActivityDiagramFile("testdata/test_file1.add")); // Assert the diagram is loaded correctly 
	EXPECT_TRUE(_activityDiagram.isExistPathBetween(0, 8));
	int idCount = _activityDiagram._idCount;
	int id = _activityDiagram.addGlyphCommand(EDGE, "Test");
	EXPECT_EQ(id, idCount); // Assert the edge is added correctly
	EXPECT_EQ(_activityDiagram.connectGlyphCommand(4, 12), ActivityDiagram::SUCCESS);
	EXPECT_TRUE(_activityDiagram.isConnected(4, 12)); // Assert glyph 4 and 12 are connected 
	EXPECT_TRUE(_activityDiagram.undo());
	EXPECT_FALSE(_activityDiagram.isConnected(4, 12)); // Assert there is no connection between glyph 4and 12
	EXPECT_TRUE(_activityDiagram.redo());
	EXPECT_TRUE(_activityDiagram.isConnected(4, 12)); // Assert glyph 4 and 12 are connected 
}

TEST_F(ActivityDiagramTest, testCommonUsage)
{
	EXPECT_TRUE(_activityDiagram.loadActivityDiagramFile("testdata/test_file1.add")); // Assert the diagram is loaded correctly 
	int idCount_Activity = _activityDiagram._idCount;
	int id_Activity = _activityDiagram.addGlyphCommand(ACTIVITY, "New Activity 12"); 
	EXPECT_EQ(id_Activity, idCount_Activity); // Assert the activity is added correctly 
	int idCount_Edge = _activityDiagram._idCount;
	int id_Edge = _activityDiagram.addGlyphCommand(EDGE, "New Edge 13"); 
	EXPECT_EQ(id_Edge, idCount_Edge); // Assert the edge is added correctly 
	EXPECT_EQ(_activityDiagram.connectGlyphCommand(4, 13), ActivityDiagram::SUCCESS); 
	EXPECT_TRUE(_activityDiagram.isConnected(4, 13)); // Assert glyph 4 and 12 are connected 
	EXPECT_EQ(_activityDiagram.connectGlyphCommand(13, 12), ActivityDiagram::SUCCESS); 
	EXPECT_TRUE(_activityDiagram.isConnected(13, 12)); // Assert glyph 13 and 12 are connected 
	EXPECT_TRUE(_activityDiagram.isExistPathBetween(4, 12)); // Assert there exists a path
	EXPECT_TRUE(_activityDiagram.deleteGlyphCommand(id_Activity)); 
	EXPECT_TRUE(_activityDiagram.getGlyphById(id_Activity) == NULL); // Assert the activity has been deleted
	EXPECT_FALSE(_activityDiagram.isConnected(13, 12)); // Assert there is no connection between glyph 13and 12
	EXPECT_TRUE(_activityDiagram.undo());
	EXPECT_EQ(_activityDiagram.getGlyphById(id_Activity)->getText(), "New Activity 12"); // Assert there is an activity with text ¡§New Activity 12¡¨
	EXPECT_TRUE(_activityDiagram.isConnected(13, 12)); // Assert glyph 13 and 12 are connected 
	EXPECT_TRUE(_activityDiagram.redo());
	EXPECT_TRUE(_activityDiagram.getGlyphById(id_Activity) == NULL); // Assert the activity has been deleted 
	EXPECT_FALSE(_activityDiagram.isConnected(13, 12)); // 21. Assert glyph 13 and 12 are connected 
	int idCount_DecisionNode = _activityDiagram._idCount;
	int id_DecisionNode = _activityDiagram.addGlyphCommand(DECISION_NODE, ""); 
	EXPECT_EQ(id_DecisionNode, idCount_DecisionNode); // 23. Assert the decision is added correctly
	EXPECT_TRUE(_activityDiagram.connectGlyph(13, 14));
	EXPECT_TRUE(_activityDiagram.isConnected(13, 14)); // 25. Assert glyph 13and 14are connected 
	EXPECT_TRUE(_activityDiagram.isExistPathBetween(0, 14)); // 27. Assert there exists a path 
	EXPECT_TRUE(_activityDiagram.deleteGlyphCommand(id_Edge));
	EXPECT_TRUE(_activityDiagram.getGlyphById(id_Edge) == NULL); // 29. Assert the edge has been deleted
	EXPECT_FALSE(_activityDiagram.isExistPathBetween(0, 14)); // 31. Assert there is no path 
}