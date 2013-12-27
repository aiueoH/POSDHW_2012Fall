#include "PresentationModel.h"

PresentationModel::PresentationModel(ActivityDiagram *activityDiagram)
{
	_activityDiagram = activityDiagram;
	_pointState = new PointState(this);
	_addGlyphState = new AddGlyphState(this);
	_connectState = new ConnectState(this);

	_isToolBarButtonIsExistPathBetweenEnabled = false;
	_isToolBarButtonOpenFileEnabled = true;
	_isToolBarButtonPointChecked = false;
	_isToolBarButtonConnectChecked = false;
	_isToolBarButtonAddActivityChecked = false;
	_isToolBarButtonAddDecisionNodeChecked = false;
	_isToolBarButtonAddInitialNodeChecked = false;
	_isToolBarButtonAddFinalNodeChecked = false;
	_isToolBarButtonAddEdgeChecked = false;

	_isKeyControlPress = false;
	_isMouseLeftPress = false;

	setPointState();
}

PresentationModel::~PresentationModel(void)
{
	delete _pointState;
	delete _addGlyphState;
	delete _connectState;
}

bool PresentationModel::loadActivityDiagramFile(string fileName)
{
	return _activityDiagram->loadActivityDiagramFile(fileName);
}

vector<int> PresentationModel::getGlyphIds()
{
	return _activityDiagram->getGlyphIds();
}

vector<Glyph*> PresentationModel::getSelectedGlyphs()
{
	return _activityDiagram->getSelectedGlyphs();
}

bool PresentationModel::isExistPathBetween()
{
	return _activityDiagram->isExistPathBetween();
}

void PresentationModel::layoutGlyphs()
{
	_activityDiagram->layoutGlyphs();
}

bool PresentationModel::isToolBarButtonOpenFileEnabled()
{
	return _isToolBarButtonOpenFileEnabled;
}

bool PresentationModel::isToolBarButtonIsExistPathBetweenEnabled()
{
	return _isToolBarButtonIsExistPathBetweenEnabled;
}

void PresentationModel::isKeyControlPress(bool is)
{
	_isKeyControlPress = is;
	notify();
}

void PresentationModel::isMouseLeftPress(bool is)
{
	_isMouseLeftPress = is;
	notify();
}

bool PresentationModel::isToolBarButtonPointChecked()
{
	return _isToolBarButtonPointChecked;
}

bool PresentationModel::isToolBarButtonConnectChecked()
{
	return _isToolBarButtonConnectChecked;
}

bool PresentationModel::isToolBarButtonAddActivityChecked()
{
	return _isToolBarButtonAddActivityChecked;
}

bool PresentationModel::isToolBarButtonAddDecisionNodeChecked()
{
	return _isToolBarButtonAddDecisionNodeChecked;
}

bool PresentationModel::isToolBarButtonAddInitialNodeChecked()
{
	return _isToolBarButtonAddInitialNodeChecked;
}

bool PresentationModel::isToolBarButtonAddFinalNodeChecked()
{
	return _isToolBarButtonAddFinalNodeChecked;
}

bool PresentationModel::isToolBarButtonAddEdgeChecked()
{
	return _isToolBarButtonAddEdgeChecked;
}

bool PresentationModel::isToolBarButtonRedoEnabled()
{
	return _activityDiagram->canRedo();
}

bool PresentationModel::isToolBarButtonUndoEnabled()
{
	return _activityDiagram->canUndo();
}

bool PresentationModel::isToolBarButtonPasteEnabled()
{
	return _activityDiagram->canPaste();
}

bool PresentationModel::isToolBarButtonCopyEnabled()
{
	if (_activityDiagram->getSelectedGlyphsCount() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool PresentationModel::isToolBarButtonCutEnabled()
{
	if (_activityDiagram->getSelectedGlyphsCount() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool PresentationModel::isToolBarButtonDeleteEnabled()
{
	if (_activityDiagram->getSelectedGlyphsCount() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void PresentationModel::mouseEvent(int x, int y, MOUSE_EVENT_TYPE type)
{
	InputInformation inputInformation = createInputInformation(x, y);

	switch (type)
	{
	case LEFT_BUTTON_PRESS :
		_presentationModelState->mousePressEvent(inputInformation);
		break;
	case LEFT_BUTTON_RELEASE :
		_presentationModelState->mouseReleaseEvent(inputInformation);
		break;
	case MOVE :
		_presentationModelState->mouseMoveEvent(inputInformation);
		break;
	}
}

int PresentationModel::getGlyphIdByCoordinate(int x, int y)
{
	return _activityDiagram->getGlyphByCoordinate(x, y);
}

void PresentationModel::setGlyphIsSelected(Glyph *glyph, bool is)
{
	_activityDiagram->setGlyphIsSelected(glyph, is);
}

void PresentationModel::setAllGlyphIsSelected(bool is)
{
	_activityDiagram->setAllGlyphsIsSelected(is);
}

void PresentationModel::setPointState()
{
	setAllEdgeHasConnectionPoint(false);
	setAllCheckableButtonsIsChecked(false);
	_presentationModelState = _pointState;
	_isToolBarButtonPointChecked = true;
	notify();
}

void PresentationModel::setAddGlyphState(GLYPH_TYPE type, string text)
{
	_presentationModelState = _addGlyphState;
	_addGlyphType = type;
	_addGlyphText = text;

	setAllEdgeHasConnectionPoint(false);
	setAllCheckableButtonsIsChecked(false);
	switch (type)
	{
	case ACTIVITY:
		_isToolBarButtonAddActivityChecked = true;
		break;
	case  DECISION_NODE:
		_isToolBarButtonAddDecisionNodeChecked = true;
		break;
	case EDGE:
		_isToolBarButtonAddEdgeChecked = true;
		break;
	case INITIAL_NODE:
		_isToolBarButtonAddInitialNodeChecked = true;
		break;;
	case FINAL_NODE:
		_isToolBarButtonAddFinalNodeChecked = true;
		break;
	}
	notify();
}

void PresentationModel::setConnectState()
{
	_presentationModelState = _connectState;
	setAllEdgeHasConnectionPoint(true);
	setAllCheckableButtonsIsChecked(false);
	_isToolBarButtonConnectChecked = true;
	notify();
}

void PresentationModel::setIsToolBarButtonIsExistPathBetweenEnabled(bool is)
{
	_isToolBarButtonIsExistPathBetweenEnabled = is;
	notify();
}

void PresentationModel::setAllCheckableButtonsIsChecked(bool is)
{	
	_isToolBarButtonPointChecked = is;
	_isToolBarButtonConnectChecked = is;
	_isToolBarButtonAddActivityChecked = is;
	_isToolBarButtonAddDecisionNodeChecked = is;
	_isToolBarButtonAddInitialNodeChecked = is;
	_isToolBarButtonAddFinalNodeChecked = is;
	_isToolBarButtonAddEdgeChecked = is;
	notify();
}

void PresentationModel::setAllEdgeHasConnectionPoint(bool has)
{
	_activityDiagram->setAllEdgeHasConnectionPoint(has);
}

InputInformation PresentationModel::createInputInformation(int x, int y)
{
	InputInformation inputInformation;
	inputInformation.addGlyphType = _addGlyphType;
	inputInformation.text = _addGlyphText;
	inputInformation.x = x;
	inputInformation.y = y;
	inputInformation.isKeyControlPress = _isKeyControlPress;
	inputInformation.isMouseLeftPress = _isMouseLeftPress;

	return inputInformation;
}

void PresentationModel::addGlyphCommand(GlyphProperty property)
{
	_activityDiagram->addGlyphCommand(property);
}

void PresentationModel::connectGlyphCommand(int fromId, int toId)
{
	_activityDiagram->connectGlyphCommand(fromId, toId);
}

int PresentationModel::getGlyphByCoordinateOnTargetConnectionPoint(int x, int y)
{
	return _activityDiagram->getGlyphByCoordinateOnTargetConnectionPoint(x, y);
}

int PresentationModel::getGlyphByCoordinateOnSourceConnectionPoint(int x, int y)
{
	return _activityDiagram->getGlyphByCoordinateOnSourceConnectionPoint(x, y);
}

void PresentationModel::deleteConnection(int fromId, int toId)
{
	_activityDiagram->deleteConnection(fromId, toId);
}

void PresentationModel::setGlyphText(int id, string text)
{
	_activityDiagram->setGlyphText(id, text);
}

void PresentationModel::setGlyphX(int id, int x)
{
	_activityDiagram->setGlyphX(id, x);
}

void PresentationModel::setGlyphY(int id, int y)
{
	_activityDiagram->setGlyphY(id, y);
}

void PresentationModel::setGlyphHeight(int id, int height)
{
	_activityDiagram->setGlyphHeight(id, height);
}

void PresentationModel::setGlyphWidth(int id, int width)
{
	_activityDiagram->setGlyphWidth(id, width);
}

void PresentationModel::setIsSelected(int id, bool isSelected)
{
	_activityDiagram->setIsSelected(id, isSelected);
}

void PresentationModel::setHasConnectionPoint(int id, bool hasConnectionPoint)
{
	_activityDiagram->setHasConnectionPoint(id, hasConnectionPoint);
}

bool PresentationModel::getIsSelected(int id)
{
	return _activityDiagram->getIsSelected(id);
}

vector<int> PresentationModel::getGlyphTargetIds(int id)
{
	return _activityDiagram->getGlyphTargetIds(id);
}

vector<int> PresentationModel::getGlyphSourceIds(int id)
{
	return _activityDiagram->getGlyphSourceIds(id);
}

GLYPH_TYPE PresentationModel::getGlyphType(int id)
{
	return _activityDiagram->getGlyphType(id);
}

vector<DrawInstruction> PresentationModel::getDrawInstructions(int id)
{
	return _activityDiagram->getDrawInstructions(id);
}

void PresentationModel::editTextCommand(int id, string text)
{
	_activityDiagram->editTextCommand(id, text);
}

void PresentationModel::redo()
{
	_activityDiagram->redo();
}

void PresentationModel::undo()
{
	_activityDiagram->undo();
}

GlyphProperty PresentationModel::getGlyphProperty(int id)
{
	return _activityDiagram->getGlyphProperty(id);
}

vector<GlyphProperty> PresentationModel::getGlyphPropertys(vector<int> ids)
{
	return _activityDiagram->getGlyphPropertys(ids);
}

vector<int> PresentationModel::getSelectedGlyphIds()
{
	return _activityDiagram->getSelectedGlyphIds();
}

void PresentationModel::moveGlyphCommand(vector<int> ids, vector<pair<GlyphProperty, GlyphProperty>> propertys)
{
	_activityDiagram->moveGlyphCommand(ids, propertys);
}

void PresentationModel::update()
{
	notify();
}

void PresentationModel::deleteGlyphCommand(vector<int> ids)
{
	_activityDiagram->deleteGlyphCommand(ids);
}

void PresentationModel::deleteGlyph()
{
	_activityDiagram->deleteGlyphCommand(_activityDiagram->getSelectedGlyphIds());
}

void PresentationModel::saveFile(string fileName)
{
	_activityDiagram->saveFile(fileName);
}

void PresentationModel::copy()
{
	_activityDiagram->copy();
}

void PresentationModel::cut()
{
	_activityDiagram->cut();
}

void PresentationModel::paste()
{
	_activityDiagram->paste();
}