#include "StdAfx.h"
#include "TextUi.h"

TextUi::TextUi(ActivityDiagram *activityDiagram)
{
	_isExit = false;
	_activityDiagram = activityDiagram;

	// main menu 對應之 function
	_menuOptionFunction_map.insert(pair<MENU_OPTION, MENU_OPTION_FUNCTION>(LOAD_FILE, &TextUi::loadActivityDiagramFile));
	_menuOptionFunction_map.insert(pair<MENU_OPTION, MENU_OPTION_FUNCTION>(ADD_GLYPH, &TextUi::addGlyph));
	_menuOptionFunction_map.insert(pair<MENU_OPTION, MENU_OPTION_FUNCTION>(CONNECT_GLYPH, &TextUi::connectTwoGlyphs));
	_menuOptionFunction_map.insert(pair<MENU_OPTION, MENU_OPTION_FUNCTION>(DISPLAY_DIAGRAM, &TextUi::displayTheCurrentDiagram));
	_menuOptionFunction_map.insert(pair<MENU_OPTION, MENU_OPTION_FUNCTION>(IS_THERE_PATH, &TextUi::isThereAPathBetweenTwoGlyphs));
	_menuOptionFunction_map.insert(pair<MENU_OPTION, MENU_OPTION_FUNCTION>(DELETE_A_GLYPH, &TextUi::deleteAGlyph));
	_menuOptionFunction_map.insert(pair<MENU_OPTION, MENU_OPTION_FUNCTION>(UNDO, &TextUi::undo));
	_menuOptionFunction_map.insert(pair<MENU_OPTION, MENU_OPTION_FUNCTION>(REDO, &TextUi::redo));
	_menuOptionFunction_map.insert(pair<MENU_OPTION, MENU_OPTION_FUNCTION>(EXIT, &TextUi::exit));
	// 各Glyph新增對應之 function
	_addGlyphFunction_map.insert(pair<GLYPH_TYPE, ADD_GLYPH_FUNCTION>(INITIAL_NODE, &TextUi::addInitialNode));
	_addGlyphFunction_map.insert(pair<GLYPH_TYPE, ADD_GLYPH_FUNCTION>(FINAL_NODE, &TextUi::addFinalNode));
	_addGlyphFunction_map.insert(pair<GLYPH_TYPE, ADD_GLYPH_FUNCTION>(ACTIVITY, &TextUi::addActivity));
	_addGlyphFunction_map.insert(pair<GLYPH_TYPE, ADD_GLYPH_FUNCTION>(EDGE, &TextUi::addEdge));
	_addGlyphFunction_map.insert(pair<GLYPH_TYPE, ADD_GLYPH_FUNCTION>(DECISION_NODE, &TextUi::addDecisionNode));
}

TextUi::~TextUi(void)
{
}

void TextUi::startUi()
{
	do 
	{
		displayMenu();
		processCommand();
	} while (!_isExit);
}

void TextUi::displayMenu()
{
	cout << "1. Load activity diagram file" << endl;
	cout << "2. Add a glyph" << endl;
	cout << "3. Connect two glyphs" << endl;
	cout << "4. Display the current diagram" << endl;
	cout << "5. Is there a path between two glyphs?" << endl;
	cout << "6. Delete a glyph" << endl;
	cout << "7. Undo" << endl;
	cout << "8. Redo" << endl;
	cout << "9. Exit" << endl;
}

void TextUi::processCommand()
{
	MENU_OPTION option = (MENU_OPTION)getInt();

	if (_menuOptionFunction_map.find(option) != _menuOptionFunction_map.end()) // map 裡有這個 key(option)
		(this->*(_menuOptionFunction_map[option]))(); // 執行對應的 function
	else
		cout << "You entered an invalid selection." << endl;
}

void TextUi::loadActivityDiagramFile()
{
	cout << "Please key in a file path: ";
	string file = getString();
	if (_activityDiagram->loadActivityDiagramFile(file))
	{
		displayGlyphs();
		displayConnections();
	} 
	else
	{
		cout << "Can not open file." << endl;
	}
}

void TextUi::addGlyph()
{
	cout << "What kind of glyph do you want to add?" << endl;
	cout << "[I]Initial node [F]Final node [A]Activity [E]Edge [D]Decision node" << endl;
	bool canBreak = false;
	do 
	{
		GLYPH_TYPE type = (GLYPH_TYPE)getChar();
		if (_addGlyphFunction_map.find(type) != _addGlyphFunction_map.end()) // map 裡有這個 key(type)
		{
			(this->*(_addGlyphFunction_map[type]))(); // 執行對應的 function
			canBreak = true;
		}
		else
		{
			cout << "You entered an invalid glyph. Please enter a valid one again." << endl;
		}
	} while (!canBreak);
	displayGlyphs();
}

void TextUi::connectTwoGlyphs()
{
	int firstGlyphId, secondGlyphId;

	cout << "Please enter the first glyph ID" << endl;
	firstGlyphId = getGlyphId();
	cout << "Please enter the second glyph ID" << endl;
	secondGlyphId = getGlyphId();
	
	ActivityDiagram::CONNECT_ERROR_TYPE connect_error_code = (ActivityDiagram::CONNECT_ERROR_TYPE)_activityDiagram->connectGlyphCommand(firstGlyphId, secondGlyphId);
	switch (connect_error_code)
	{
	case ActivityDiagram::SUCCESS:
		cout << "The glyph '" << firstGlyphId << "' has been connected to glyph '" << secondGlyphId << "'." << endl;
		displayConnections();
		break;
	case ActivityDiagram::CONNECT_ITSELF:
		cout << "The glyph '" << firstGlyphId << "' cannot connect to itself." << endl;
		break;
	case ActivityDiagram::CANNOT_BE_CONNECTED:
		cout << "The glyph '" << secondGlyphId << "' cannot be connected by other glyphs." << endl;
		break;
	case ActivityDiagram::CANNOT_CONNECT:
		cout << "The glyph '" << firstGlyphId << "' cannot connect to other glyphs." << endl;
		break;
	case ActivityDiagram::OTHER_ERROR:
		cout << "The glyph '" << firstGlyphId << "' cannot connect to glyph '" << secondGlyphId << "'." << endl;
		break;
	}
}

void TextUi::displayTheCurrentDiagram()
{
	displayGlyphs();
	displayConnections();
}

void TextUi::isThereAPathBetweenTwoGlyphs()
{
	int firstGlyphId, secondGlyphId;

	cout << "Please enter the first glyph ID" << endl;
	firstGlyphId = getGlyphId();
	cout << "Please enter the second glyph ID" << endl;
	secondGlyphId = getGlyphId();

	if (_activityDiagram->isExistPathBetween(firstGlyphId, secondGlyphId))
		cout << "There exists a path linking the two glyphs." << endl;
	else
		cout << "There is no path linked the two glyphs." << endl;
}

void TextUi::deleteAGlyph()
{
	cout << "Please enter the glyph ID" << endl;
	int id = getGlyphId();
	if (_activityDiagram->deleteGlyphCommand(id))
	{	
		cout << "The glyph '" << id << "' has been deleted." << endl;
		displayTheCurrentDiagram();
	}
	else
	{
		cout << "The glyph '" << id << "' can't delete." << endl;
	}

}

void TextUi::undo()
{
	if (_activityDiagram->undo())
	{
		cout << "Undo!" << endl;
		displayTheCurrentDiagram();
	}
	else
	{
		cout << "Can't undo." << endl;
	}
}

void TextUi::redo()
{
	if (_activityDiagram->redo())
	{
		cout << "Redo!" << endl;
		displayTheCurrentDiagram();
	}
	else
	{
		cout << "Can't redo." << endl;
	}
}

void TextUi::exit()
{
	cout << "Goodbye!" << endl;
	_isExit = true;
}

void TextUi::displayAddGlyph()
{
	cout << "What kind of glyph do you want to add?" << endl;
	cout << "[I]Initial node [F]Final node [A]Activity [E]Edge [D]Decision node" << endl;
}

void TextUi::addInitialNode()
{
	int id = _activityDiagram->addGlyphCommand(INITIAL_NODE, "");
	Glyph *glyph = _activityDiagram->getGlyphById(id);
	cout << "A glyph [Initial node] has been added. ID: " << glyph->getId() << endl;
}

void TextUi::addFinalNode()
{
	int id = _activityDiagram->addGlyphCommand(FINAL_NODE, "");
	Glyph *glyph = _activityDiagram->getGlyphById(id);
	cout << "A glyph [Initial node] has been added. ID: " << glyph->getId() << endl;
}

void TextUi::addActivity()
{
	string text = getGlyphText();
	int id = _activityDiagram->addGlyphCommand(ACTIVITY, text);
	Glyph *glyph = _activityDiagram->getGlyphById(id);
	cout << "A glyph [Activity] has been added. ID: " << glyph->getId() << ", Text: \"" << glyph->getText() << "\"" << endl;
}

void TextUi::addEdge()
{
	string text = getGlyphText();
	int id = _activityDiagram->addGlyphCommand(EDGE, text);
	Glyph *glyph = _activityDiagram->getGlyphById(id);
	cout << "A glyph [Edge] has been added. ID: " << glyph->getId() << ", Text: \"" << glyph->getText() << "\"" << endl;
}

void TextUi::addDecisionNode()
{
	int id = _activityDiagram->addGlyphCommand(DECISION_NODE, "");
	Glyph *glyph = _activityDiagram->getGlyphById(id);
	cout << "A glyph [Decision node] has been added. ID: " << glyph->getId() << endl;
}

int TextUi::getGlyphId()
{
	int id;
	do 
	{
		id = getInt();
		if (_activityDiagram->getGlyphById(id) != NULL)
			break;	
		else
			cout << "The glyph ID you entered does not exist. Please enter a valid one again." << endl;
	} while (true);
	return id;
}

int TextUi::getInt()
{
	string input;
	bool canBreak = true;
	while (true) 
	{
		cout << "> ";
		getline(cin, input);
		if (canStringToInt(input)) // 判斷可以正確轉換為字串。不可正確轉換範例 : "123A456"
			break;
		else
			cout << "The glyph ID you entered does not exist. Please enter a valid one again." << endl;
	}
	return atoi(input.c_str());
}

char TextUi::getChar()
{
	string input;
	while (true)
	{
		cout << "> ";
		getline(cin, input);
		if (input.length() == sizeof(char)) // 只接受一個字元
			break;
		else
			cout << "You entered an invalid character." << endl;
	}
	return input[FIRST_CHAR_INDEX_OF_STRING];
}

string TextUi::getGlyphText()
{
	cout << "Enter the text on this glyph:" << endl;
	cout << "> ";
	return getString();
}

void TextUi::displayGlyphs()
{
	vector<int> glyphIds = _activityDiagram->getGlyphIds();

	cout << "Glyphs:" << endl;
	cout << "------------------------------------" << endl;
	cout << " Type |  ID  |  Text" << endl;
	cout << "------+------+----------------------" << endl;

	for (unsigned int i = 0; i < glyphIds.size(); i++)
	{
		GlyphProperty property = _activityDiagram->getGlyphProperty(glyphIds[i]);
		string typeName = Glyph::typeEnumToString(property.type);
		string text = property.text;
		int id = property.id;
		printf("  %s   |  %2d  |  %s\n", typeName.c_str(), id, text.c_str());
	}

	cout << "------------------------------------" << endl;
}

void TextUi::displayConnections()
{
	vector<pair<Glyph*, Glyph*>> connections = _activityDiagram->getConnections();

	cout << "Connections:" << endl;
	cout << "--------------" << endl;
	cout << " From |  To  |" << endl;
	cout << "------+------|" << endl;

	for (unsigned int i = 0; i < connections.size(); i++)
	{
		int fromId = connections[i].first->getId();
		int toId = connections[i].second->getId();
		printf("  %2d  |  %2d  |\n",fromId, toId); 
	}

	cout << "--------------" << endl;
}

bool TextUi::canStringToInt(string s)
{
	for (unsigned int i = 0; i < s.length(); i++)
		if (!(s[i] >= '0' && s[i] <= '9'))
			return false;
	return true;
}

string TextUi::getString()
{
	string str;
	getline(cin, str);
	return str;
}