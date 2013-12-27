#ifndef PRESENTATIONMODEL_H_
#define PRESENTATIONMODEL_H_

#include "Glyph.h"
struct InputInformation;
#include "ActivityDiagram.h"
#include "PresentationModelState.h"
#include "PointState.h"
#include "AddGlyphState.h"
#include "ConnectState.h"
#include "Subject.h"
#include "Observer.h"
class PointState;
class AddGlyphState;
class ConnectState;

#include <vector>

class PresentationModel :
	public Observer, public Subject
{
private:
	ActivityDiagram *_activityDiagram;

	bool _isToolBarButtonIsExistPathBetweenEnabled;
	bool _isToolBarButtonOpenFileEnabled;
	bool _isToolBarButtonPointChecked;
	bool _isToolBarButtonConnectChecked;
	// add glyph
	bool _isToolBarButtonAddActivityChecked;
	bool _isToolBarButtonAddDecisionNodeChecked;
	bool _isToolBarButtonAddInitialNodeChecked;
	bool _isToolBarButtonAddFinalNodeChecked;
	bool _isToolBarButtonAddEdgeChecked;
	// input control state
	bool _isKeyControlPress;
	bool _isMouseLeftPress;
	// state pattern
	PresentationModelState *_presentationModelState;
	PointState *_pointState;
	AddGlyphState *_addGlyphState;
	ConnectState *_connectState;
	GLYPH_TYPE _addGlyphType;
	string _addGlyphText;

	InputInformation createInputInformation(int x, int y);
	void update();

public:
	enum MOUSE_EVENT_TYPE {LEFT_BUTTON_PRESS, LEFT_BUTTON_RELEASE, MOVE};

	PresentationModel(ActivityDiagram *activityDiagram);
	~PresentationModel(void);

	bool loadActivityDiagramFile(string fileName);	
	bool isExistPathBetween();
	void layoutGlyphs();
	void addGlyphCommand(GlyphProperty property);
	void connectGlyphCommand(int fromId, int toId);
	void deleteConnection(int fromId, int toId);
	void deleteGlyphCommand(vector<int> ids);
	void editTextCommand(int id, string text);
	void moveGlyphCommand(vector<int> ids, vector<pair<GlyphProperty, GlyphProperty>> propertys);
	void deleteGlyph();
	void copy();
	void cut();
	void paste();
	void redo();
	void undo();
	void mouseEvent(int x, int y, MOUSE_EVENT_TYPE type);
	void saveFile(string fileName);
	///////////////////////////////////////////////////////////////////////
	// set
	///////////////////////////////////////////////////////////////////////
	// state pattern
	void setPointState();
	void setAddGlyphState(GLYPH_TYPE type, string text);
	void setConnectState();
	// glyph
	void setGlyphText(int id, string text);
	void setGlyphX(int id, int x);
	void setGlyphY(int id, int y);
	void setGlyphHeight(int id, int height);
	void setGlyphWidth(int id, int width);
	void setIsSelected(int id, bool isSelected);
	void setHasConnectionPoint(int id, bool hasConnectionPoint);

	void setGlyphIsSelected(Glyph *glyph, bool is);
	void setAllGlyphIsSelected(bool is);
	void setAllEdgeHasConnectionPoint(bool has);
	// gui
	void setIsToolBarButtonIsExistPathBetweenEnabled(bool is);
	void setAllCheckableButtonsIsChecked(bool is);
	void isKeyControlPress(bool is);
	void isMouseLeftPress(bool is);
	///////////////////////////////////////////////////////////////////////
	// get
	///////////////////////////////////////////////////////////////////////
	bool getIsSelected(int id);
	GlyphProperty getGlyphProperty(int id);
	vector<GlyphProperty> getGlyphPropertys(vector<int> ids);
	GLYPH_TYPE getGlyphType(int id);
	vector<int> getGlyphIds();
	vector<Glyph*> getSelectedGlyphs();
	vector<int> getSelectedGlyphIds();
	vector<int> getGlyphTargetIds(int id);
	vector<int> getGlyphSourceIds(int id);
	vector<DrawInstruction> getDrawInstructions(int id);
	int getGlyphIdByCoordinate(int x, int y);
	int getGlyphByCoordinateOnTargetConnectionPoint(int x, int y);
	int getGlyphByCoordinateOnSourceConnectionPoint(int x, int y);
	// button enabled
	bool isToolBarButtonOpenFileEnabled();
	bool isToolBarButtonIsExistPathBetweenEnabled();
	bool isToolBarButtonRedoEnabled();
	bool isToolBarButtonUndoEnabled();
	bool isToolBarButtonCopyEnabled();
	bool isToolBarButtonCutEnabled();
	bool isToolBarButtonPasteEnabled();
	bool isToolBarButtonDeleteEnabled();
	// button checked
	bool isToolBarButtonPointChecked();
	bool isToolBarButtonConnectChecked();
	bool isToolBarButtonAddActivityChecked();
	bool isToolBarButtonAddDecisionNodeChecked();
	bool isToolBarButtonAddInitialNodeChecked();
	bool isToolBarButtonAddFinalNodeChecked();
	bool isToolBarButtonAddEdgeChecked();

};

struct InputInformation
{
	int x, y;
	bool isKeyControlPress;
	bool isMouseLeftPress;
	GLYPH_TYPE addGlyphType;
	string text;
};

#endif