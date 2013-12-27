#ifndef ACTIVITYDIAGRAM_H_
#define ACTIVITYDIAGRAM_H_

#include "Globle.h"
#include "GlyphFactory.h"
#include "CommandManager.h"
#include "Command.h"
#include "Tool.h"
class ActivityDiagram;
#include "AddGlyphCommand.h"
#include "ConnectGlyphCommand.h"
#include "DeleteGlyphCommand.h"
#include "EditTextCommand.h"
#include "MoveGlyphCommand.h"
#include "PresentationModel.h"
#include "Subject.h"
#include "GlyphVisitor.h"
#include "SaveGlyphVisitor.h"
#include "LayoutGlyphVisitor.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <gtest/gtest_prod.h>

using namespace std;

class ActivityDiagram :
	public Subject
{
private:
	FRIEND_TEST(ActivityDiagramTest, testUndoDeleteGlyph);
	FRIEND_TEST(ActivityDiagramTest, testRedoConnectGlyphs);
	FRIEND_TEST(ActivityDiagramTest, testCommonUsage);
	FRIEND_TEST(ActivityDiagramTest, visitGlyphs);
	FRIEND_TEST(ActivityDiagramTest, isVisited);
	FRIEND_TEST(ActivityDiagramTest, deleteGlyphsMemory);
	FRIEND_TEST(ActivityDiagramTest, addGlyphCommand);

	enum READ_LINE_MODE {READ_GLYPH, READ_CONNECTION};
	
	static const int ID_COUNT_INITIAL = 0; // idCount 的初始值
	static const int INPUT_CHAR_MAX_LENGTH = 1; // getChar()用

	CommandManager _commandManager;

	int _idCount;
	vector<Glyph*> _glyphs, _copyGlyphs;
	vector<pair<Glyph*, Glyph*>> _connections;
	
	bool isVisited(Glyph *glyph, vector<Glyph*> *visitedGlyphs);
	bool visitGlyphs(Glyph *goalGlyph,Glyph *currentGlyph, vector<Glyph*> *visitedGlyphs);
	void deleteGlyphsMemory();
	void deleteCopyGlyphsMemory();
	void writeFile(ofstream *fout, vector<string> lines);
	void connectCopyGlyph(vector<Glyph*> sampleGlyphs, map<Glyph*, Glyph*> glyphMap);

public:
	ActivityDiagram(void);
	~ActivityDiagram(void);

	enum CONNECT_ERROR_TYPE {
		SUCCESS, 
		CONNECT_ITSELF, 
		CANNOT_BE_CONNECTED, 
		CANNOT_CONNECT, 
		OTHER_ERROR};
	
	// command
	int addGlyphCommand(GlyphProperty property);
	int addGlyphCommand(GLYPH_TYPE type, string text);
	int addGlyphCommand(string str);
	ActivityDiagram::CONNECT_ERROR_TYPE connectGlyphCommand(int fromId, int toId);
	ActivityDiagram::CONNECT_ERROR_TYPE connectGlyphCommand(string str);
	bool deleteGlyphCommand(int id);
	bool deleteGlyphCommand(vector<int> ids);
	void editTextCommand(int id, string text);
	void moveGlyphCommand(vector<int> ids, vector<pair<GlyphProperty, GlyphProperty>> propertys);
	void copy();
	void cut();
	void paste();
	bool undo();
	bool redo();
	bool canUndo();
	bool canRedo();

	// 實際功能
	bool loadActivityDiagramFile(string fileName);
	Glyph* addGlyph(GlyphProperty property);
	Glyph* addGlyph(int id, GLYPH_TYPE type, string text);
	Glyph* addGlyph(int id, GLYPH_TYPE type, string text, int index);
	bool connectGlyph(int fromId, int toId);
	bool isExistPathBetween(int fromId, int toId);
	bool isExistPathBetween();
	bool deleteGlyph(int id);
	bool deleteConnection(int fromId, int toId);
	void saveFile(string fileName);

	Glyph* getGlyphById(int id);

	void setGlyphProperty(int id, GlyphProperty property);
	void setGlyphText(int id, string text);
	void setGlyphX(int id, int x);
	void setGlyphY(int id, int y);
	void setGlyphHeight(int id, int height);
	void setGlyphWidth(int id, int width);
	void setIsSelected(int id, bool isSelected);
	void setHasConnectionPoint(int id, bool hasConnectionPoint);

	// gui
	void setGlyphIsSelected(Glyph *glyph, bool is);
	void setAllGlyphsIsSelected(bool is);
	void setAllEdgeHasConnectionPoint(bool has);
	void deselectedAllGlyphs();
	int getGlyphByCoordinate(int x, int y);
	int getGlyphByCoordinateOnTargetConnectionPoint(int x, int y);
	int getGlyphByCoordinateOnSourceConnectionPoint(int x, int y);

	vector<DrawInstruction> getDrawInstructions(int id);
	GLYPH_TYPE getGlyphType(int id);
	GlyphProperty getGlyphProperty(int id);
	vector<GlyphProperty> getGlyphPropertys(vector<int> ids);
	vector<int> getGlyphTargetIds(int id);
	vector<int> getGlyphSourceIds(int id);
	vector<int> getGlyphIds();
	int getGlyphIndex(int id);
	string getGlyphText(int id);
	vector<pair<Glyph*, Glyph*>> getConnections();
	int getSelectedGlyphsCount();
	vector<Glyph*> getSelectedGlyphs();
	vector<int> getSelectedGlyphIds();
	bool getIsSelected(int id);
	bool getIsLonely(int id);
	bool canPaste();

	void initial();

	bool isConnected(int fromId, int toId);
	ActivityDiagram::CONNECT_ERROR_TYPE canConnectGlyph(int fromId, int toId);
	void layoutGlyphs();
};

#endif