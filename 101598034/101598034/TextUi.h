#ifndef TEXTUI_H_
#define TEXTUI_H_

#include "ActivityDiagram.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

class TextUi
{
private:
	bool _isExit;
	ActivityDiagram *_activityDiagram;

	void displayMenu();
	void displayAddGlyph();
	void displayGlyphs();
	void displayConnections();

	void processCommand();

	// 功能項
	enum MENU_OPTION
	{
		LOAD_FILE = 1, 
		ADD_GLYPH = 2, 
		CONNECT_GLYPH = 3, 
		DISPLAY_DIAGRAM = 4, 
		IS_THERE_PATH = 5, 
		DELETE_A_GLYPH = 6, 
		UNDO = 7, 
		REDO = 8,
		EXIT = 9
	};
	typedef void (TextUi::*MENU_OPTION_FUNCTION)();
	map<MENU_OPTION, MENU_OPTION_FUNCTION> _menuOptionFunction_map;
	void loadActivityDiagramFile();
	void addGlyph();
	void connectTwoGlyphs();
	void displayTheCurrentDiagram();
	void isThereAPathBetweenTwoGlyphs();
	void deleteAGlyph();
	void undo();
	void redo();
	void exit();

	// 加入Glyph
	typedef void (TextUi::*ADD_GLYPH_FUNCTION)();
	map<GLYPH_TYPE, ADD_GLYPH_FUNCTION> _addGlyphFunction_map;
	void addInitialNode();
	void addFinalNode();
	void addActivity();
	void addEdge();
	void addDecisionNode();

	// 取得輸入
	int getInt();
	char getChar();
	string getString();
	int getGlyphId();
	string getGlyphText();

	// 工具
	bool canStringToInt(string s);
public:
	TextUi(ActivityDiagram *activityDiagram);
	~TextUi(void);

	void startUi();

};
#endif