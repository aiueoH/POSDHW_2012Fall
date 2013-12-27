#include "ActivityDiagram.h"

ActivityDiagram::ActivityDiagram(void)
{
	initial();
}

ActivityDiagram::~ActivityDiagram(void)
{
	deleteGlyphsMemory();
	deleteCopyGlyphsMemory();
}

Glyph* ActivityDiagram::addGlyph(GlyphProperty property)
{
	Glyph *glyph = GlyphFactory::createGlyph(property.id, property.type, property.text);
	_glyphs.push_back(glyph);
	setGlyphProperty(property.id, property);
	notify();
	return glyph;
}

Glyph* ActivityDiagram::addGlyph(int id, GLYPH_TYPE type, string text)
{
	Glyph *glyph = GlyphFactory::createGlyph(id, type, text);
	_glyphs.push_back(glyph);
	notify();
	return glyph;
}

/*
 * �N�s�W�� glyph ���w index ���J
 */
Glyph* ActivityDiagram::addGlyph(int id, GLYPH_TYPE type, string text, int index)
{
	Glyph *glyph = GlyphFactory::createGlyph(id, type, text);
	_glyphs.insert(_glyphs.begin() + index, glyph);
	notify();
	return glyph;
}

bool ActivityDiagram::connectGlyph(int fromId, int toId)
{
	Glyph *fromGlyph = getGlyphById(fromId);
	Glyph *toGlyph = getGlyphById(toId);
	bool result = false;
	if (fromGlyph->connectTo(toGlyph))
	{
		// �s�W�@��connection
		pair<Glyph*, Glyph*> connecion(fromGlyph, toGlyph); 
		_connections.push_back(connecion);
		result = true;
	}
	notify();

	return result;
}

bool ActivityDiagram::isExistPathBetween(int fromId, int toId)
{
	Glyph *fromGlyph = getGlyphById(fromId);
	Glyph *toGlyph = getGlyphById(toId);
	vector<Glyph*> visitedGlyphs; // �ΨӰO�����X�L��Glyph
	if (visitGlyphs(toGlyph, fromGlyph, &visitedGlyphs))
	{
		return true;
	}
	else {
		visitedGlyphs.empty();
		return visitGlyphs(fromGlyph, toGlyph, &visitedGlyphs);
	}
}

bool ActivityDiagram::isExistPathBetween()
{
	Glyph *fromGlyph = getSelectedGlyphs()[0];
	Glyph *toGlyph = getSelectedGlyphs()[1];
	vector<Glyph*> visitedGlyphs; // �ΨӰO�����X�L��Glyph
	if (visitGlyphs(toGlyph, fromGlyph, &visitedGlyphs))
	{
		return true;
	}
	else {
		visitedGlyphs.empty();
		return visitGlyphs(fromGlyph, toGlyph, &visitedGlyphs);
	}
}

bool ActivityDiagram::deleteGlyph(int id)
{
	Glyph *glyph = getGlyphById(id);

	// ���_�s��
	vector<Glyph*> targetGlyphs =  glyph->getTargets();
	for (unsigned int i = 0; i < targetGlyphs.size(); i++)
		deleteConnection(id, targetGlyphs[i]->getId());
	vector<Glyph*> sourceGlyphs =  glyph->getSources();
	for (unsigned int i = 0; i < sourceGlyphs.size(); i++)
		deleteConnection(sourceGlyphs[i]->getId(), id);

	// �q _glyphs ������
	for (unsigned int i = 0; i < _glyphs.size(); i++)
	{
		if (_glyphs[i] == glyph)
		{
			delete _glyphs[i];
			_glyphs.erase(_glyphs.begin() + i);
			notify();
			return true;
		}
	}
	notify();
	return false;	
}

/*
 * �R�� Glyph �P Glyph ���s��
 */
bool ActivityDiagram::deleteConnection(int fromId, int toId)
{
	Glyph *fromGlyph = getGlyphById(fromId);
	Glyph *toGlyph = getGlyphById(toId);

	fromGlyph->removeTarget(toGlyph);
	toGlyph->removeSource(fromGlyph);

	// ���� connection
	for (unsigned int i = 0; i < _connections.size(); i++)
		if (_connections[i].first == fromGlyph && _connections[i].second == toGlyph)
		{
			_connections.erase(_connections.begin() + i);
			notify();
			return true;
		}
	notify();
	return false;
}

/*
 * �ǥ�id���oGlyph����
 * �^��NULL�N��䤣��
 */
Glyph* ActivityDiagram::getGlyphById(int id)
{
	for(unsigned int i = 0; i < _glyphs.size(); i++)
		if (_glyphs[i]->getId() == id)
			return _glyphs[i];
	return NULL;
}

vector<int> ActivityDiagram::getGlyphIds()
{
	vector<int> ids;
	for (unsigned int i = 0; i < _glyphs.size(); i++)
	{
		ids.push_back(_glyphs[i]->getId());
	}

	return ids;
}

vector<pair<Glyph*, Glyph*>> ActivityDiagram::getConnections()
{
	return _connections;
}

/*
 * �λ��j�M�XGlyphs (DFS)
 * *targetGlyph		: �n��M�����IGlyph
 * *nextGlyph		: ��eGlyph
 * *visitedGlyphs	: �O�����X�L��Glyph (����j����|)
 */
bool ActivityDiagram::visitGlyphs(Glyph *goalGlyph,Glyph *currentGlyph, vector<Glyph*> *visitedGlyphs)
{
	if (goalGlyph == currentGlyph) // ���ؼ�Glyph
		return true;

	visitedGlyphs->push_back(currentGlyph); // �O�����X�L��Glyph

	vector<Glyph*> targetGlyphs = currentGlyph->getTargets(); // �����eGlyphs�Ҧ�target
	for (unsigned int i = 0; i < targetGlyphs.size(); i++)
		if (!isVisited(targetGlyphs[i], visitedGlyphs)) // �O�S���X�L��Glyph
			if (visitGlyphs(goalGlyph, targetGlyphs[i], visitedGlyphs)) // ���ؼ�Glyph
				return true;
			//�S���ؼ�Glyph�ɱN�~��M�X

	visitedGlyphs->pop_back(); //�h�^�W�@��Glyph
	return false;
}

bool ActivityDiagram::isVisited(Glyph *glyph, vector<Glyph*> *visitedGlyphs)
{
	if (visitedGlyphs->end() == find(visitedGlyphs->begin(), visitedGlyphs->end(), glyph)) // end == find() �N��S���M�X�L
		return false;
	return true;
}

/*
 * delete new �X�Ӫ� Glyphs (����O����)
 */
void ActivityDiagram::deleteGlyphsMemory()
{
	while (!_glyphs.empty())
	{
		delete _glyphs.back();
		_glyphs.pop_back();
	}
}

/*
 * delete copy �� Glyphs (����O����)
 */
void ActivityDiagram::deleteCopyGlyphsMemory()
{
	while (!_copyGlyphs.empty())
	{
		delete _copyGlyphs.back();
		_copyGlyphs.pop_back();
	}
}

/*
 * ��l�� ActivityDiagram
 */
void ActivityDiagram::initial()
{
	_idCount = ID_COUNT_INITIAL;
	_commandManager.initial();
	deleteGlyphsMemory();
	deleteCopyGlyphsMemory();
	_connections.clear();
	notify();
}

int ActivityDiagram::addGlyphCommand(GlyphProperty property)
{
	int id = _idCount;
	_idCount++;
	_commandManager.execute(new AddGlyphCommand(this ,id, property.type, property.text));
	
	Glyph *glyph = getGlyphById(id);
	glyph->setX(property.x);
	glyph->setY(property.y);
	glyph->setWidth(property.width);
	glyph->setHeight(property.height);

	return id;
}

int ActivityDiagram::addGlyphCommand(GLYPH_TYPE type, string text)
{
	int id = _idCount;
	_idCount++;
	_commandManager.execute(new AddGlyphCommand(this ,id, type, text));

	return id;
}

/*
 * return �Ȭ� id
 */
int ActivityDiagram::addGlyphCommand(string str)
{
	enum {TYPE_INDEX = 0, TEXT_INDEX = 1};

	vector<string> properties = Tool::splitStringToVector(Tool::trim(str), ",");
	GLYPH_TYPE type = (GLYPH_TYPE)Tool::stringToChar(properties[TYPE_INDEX]);
	string text = "";
	if (properties.size() > TEXT_INDEX) // �� text
		text = properties[TEXT_INDEX];
	return addGlyphCommand(type, text); // �s�W�æ^��id
}

ActivityDiagram::CONNECT_ERROR_TYPE ActivityDiagram::connectGlyphCommand(int fromId, int toId)
{
	CONNECT_ERROR_TYPE error = canConnectGlyph(fromId, toId);
	if (error == SUCCESS) // �i�H�s���~�u���s��
	{
		_commandManager.execute(new ConnectGlyphCommand(this, fromId, toId));
	}

	return error;
}

ActivityDiagram::CONNECT_ERROR_TYPE ActivityDiagram::connectGlyphCommand(string str)
{
	enum {FROM_ID_INDEX = 0, TO_ID_INDEX = 1};

	vector<string> ids = Tool::splitStringToVector(Tool::trim(str), ",");
	int fromId = atoi(ids[FROM_ID_INDEX].c_str());
	int toId = atoi(ids[TO_ID_INDEX].c_str());
	CONNECT_ERROR_TYPE error = connectGlyphCommand(fromId, toId);

	return error;
}

bool ActivityDiagram::deleteGlyphCommand(int id)
{

	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
	{
		vector<int> ids;
		ids.push_back(id);
		vector<int> indexs;
		indexs.push_back(getGlyphIndex(id));
		_commandManager.execute(new DeleteGlyphCommand(this, ids, indexs));
		return true;
	}

	notify();
	return false;
}

bool ActivityDiagram::deleteGlyphCommand(vector<int> ids)
{
	vector<int> indexs;
	for (unsigned int i = 0; i < ids.size(); i++)
	{
		int id = ids[i];
		indexs.push_back(getGlyphIndex(id));
	}
	_commandManager.execute(new DeleteGlyphCommand(this, ids, indexs));

	notify();
	return true;
}

void ActivityDiagram::editTextCommand(int id, string text)
{
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
	{
		_commandManager.execute(new EditTextCommand(this, id, text));
	}
	notify();
}

void ActivityDiagram::moveGlyphCommand(vector<int> ids, vector<pair<GlyphProperty, GlyphProperty>> propertys)
{
	_commandManager.execute(new MoveGlyphCommand(this, ids, propertys));
	notify();
}

bool ActivityDiagram::undo()
{
	bool result = _commandManager.undo();
	notify();
	return result;
}

bool ActivityDiagram::redo()
{
	bool result = _commandManager.redo();
	notify();
	return result;
}

bool ActivityDiagram::loadActivityDiagramFile(string fileName)
{
	initial();

	fstream file;
	string line;
	READ_LINE_MODE mode = READ_GLYPH;

	file.open(fileName, ios::in);
	if (file)
	{
		while (getline(file, line)) 
		{
			line = Tool::trim(line); // �M���h�l���ťզr��
			if (line == "") 
			{
				mode = READ_CONNECTION;
			}
			else 
			{
				if (mode == READ_GLYPH)
					addGlyphCommand(line);
				else
					connectGlyphCommand(line);
			}
		}
		file.close();
		_commandManager.initial();
		notify();
		return true;
	}
	notify();
	return false;
}

ActivityDiagram::CONNECT_ERROR_TYPE ActivityDiagram::canConnectGlyph(int fromId, int toId)
{
	Glyph *fromGlyph = getGlyphById(fromId);
	Glyph *toGlyph = getGlyphById(toId);

	if (fromGlyph == toGlyph) // �s��ۤv
		return CONNECT_ITSELF;
	else if (toGlyph->getType() == INITIAL_NODE) // �s��InitialNode
		return CANNOT_BE_CONNECTED;
	else if (fromGlyph->getType() == FINAL_NODE) // ��FinalNode�s�X
		return CANNOT_CONNECT;
	else if (fromGlyph->canAddTarget(toGlyph) && toGlyph->canAddSource(fromGlyph)) // ���\
		return SUCCESS;
	else // ��L���~
		return OTHER_ERROR;
}

/*
 * ���o Glyph �b _glyphs �� index
 */
int ActivityDiagram::getGlyphIndex(int id)
{
	Glyph *glyph = getGlyphById(id);
	for (unsigned int i = 0; i < _glyphs.size(); i++)
		if (_glyphs[i] == glyph)
			return i;

	return INDEX_OF_NOT_FOUND;
}

bool ActivityDiagram::isConnected(int fromId, int toId)
{
	for (unsigned int i = 0; i < _connections.size(); i++)
	{
		if ((_connections[i].first->getId() == fromId && 
			_connections[i].second->getId() == toId) ||
			(_connections[i].first->getId() == toId && 
			_connections[i].second->getId() == fromId))
			return true;
	}

	return false;
}

void ActivityDiagram::setGlyphIsSelected(Glyph *glyph, bool is)
{
	glyph->isSelected(is);
	notify();
}

void ActivityDiagram::setAllGlyphsIsSelected(bool is)
{
	for (unsigned int i = 0; i < _glyphs.size(); i++)
		_glyphs[i]->isSelected(is);
	notify();
}

void ActivityDiagram::setAllEdgeHasConnectionPoint(bool has)
{
	for (unsigned int i = 0; i < _glyphs.size(); i++)
		if (_glyphs[i]->getType() == EDGE)
			_glyphs[i]->setHasConnectionPoint(has);
	notify();
}

void ActivityDiagram::deselectedAllGlyphs()
{
	for (unsigned int i = 0; i < _glyphs.size(); i++)
		_glyphs[i]->isSelected(false);
	notify();
}

bool ActivityDiagram::getIsSelected(int id)
{
	return getGlyphById(id)->isSelected();
}

int	ActivityDiagram::getSelectedGlyphsCount()
{
	int count = 0;
	for (unsigned int i = 0; i < _glyphs.size(); i++)
		_glyphs[i]->isSelected() ? count++ : NULL;

	return count;
}

GlyphProperty ActivityDiagram::getGlyphProperty(int id)
{
	GlyphProperty glyphProperty;
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		glyphProperty = glyph->getProperties();
	return glyphProperty;
}

vector<Glyph*> ActivityDiagram::getSelectedGlyphs()
{
	vector<Glyph*> selectedGlyphs;
	for (unsigned int i = 0; i < _glyphs.size(); i++)
		if (_glyphs[i]->isSelected())
			selectedGlyphs.push_back(_glyphs[i]);

	return selectedGlyphs;
}

int ActivityDiagram::getGlyphByCoordinate(int x, int y)
{
	int id = -1;
	for (unsigned int i = 0; i < _glyphs.size(); i++)
	{
		if (_glyphs[i]->isOnGyph(x, y))
		{
			// component �u��
			if (_glyphs[i]->getType() != EDGE)
				return _glyphs[i]->getId();
			id = _glyphs[i]->getId();
		}
	}

	return id;
}

int ActivityDiagram::getGlyphByCoordinateOnTargetConnectionPoint(int x, int y)
{
	int id = -1;
	for (unsigned int i = 0; i < _glyphs.size(); i++)
		if (_glyphs[i]->isOnTargetConnectionPoint(x, y))
			id = _glyphs[i]->getId();

	return id;
}

int ActivityDiagram::getGlyphByCoordinateOnSourceConnectionPoint(int x, int y)
{
	int id = -1;
	for (unsigned int i = 0; i < _glyphs.size(); i++)
		if (_glyphs[i]->isOnSourceConnectionPoint(x, y))
			id = _glyphs[i]->getId();

	return id;
}

vector<GlyphProperty> ActivityDiagram::getGlyphPropertys(vector<int> ids)
{
	vector<GlyphProperty> propertys;
	for (unsigned int i = 0; i < ids.size(); i++)
	{
		propertys.push_back(getGlyphProperty(ids[i]));
	}
	return propertys;
}

bool ActivityDiagram::getIsLonely(int id)
{
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
	{
		return glyph->isLonely();
	}

	return false;
}

void ActivityDiagram::setGlyphProperty(int id, GlyphProperty property)
{
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
	{
		glyph->setText(property.text);
		glyph->setX(property.x);
		glyph->setY(property.y);
		glyph->setWidth(property.width);
		glyph->setHeight(property.height);
		glyph->isSelected(property.isSelected);
		glyph->setHasConnectionPoint(property.isSelected);
	}
	notify();
}

void ActivityDiagram::setGlyphText(int id, string text)
{
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		glyph->setText(text);
	notify();
}

void ActivityDiagram::setGlyphX(int id, int x)
{
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		glyph->setX(x);
	notify();
}

void ActivityDiagram::setGlyphY(int id, int y)
{
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		glyph->setY(y);
	notify();
}

void ActivityDiagram::setGlyphHeight(int id, int height)
{
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		glyph->setHeight(height);
	notify();
}

void ActivityDiagram::setGlyphWidth(int id, int width)
{
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		glyph->setWidth(width);
	notify();
}

void ActivityDiagram::setIsSelected(int id, bool isSelected)
{
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		glyph->isSelected(isSelected);
	notify();
}

void ActivityDiagram::setHasConnectionPoint(int id, bool hasConnectionPoint)
{
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		glyph->setHasConnectionPoint(hasConnectionPoint);
	notify();
}

vector<int> ActivityDiagram::getGlyphTargetIds(int id)
{
	Glyph *glyph = getGlyphById(id);
	vector<int> ids;
	if (glyph != NULL)
		ids = glyph->getTargetIds();
	
	return ids;
}

vector<int> ActivityDiagram::getGlyphSourceIds(int id)
{
	Glyph *glyph = getGlyphById(id);
	vector<int> ids;
	if (glyph != NULL)
		ids = glyph->getSourceIds();
	
	return ids;
}

GLYPH_TYPE ActivityDiagram::getGlyphType(int id)
{
	GLYPH_TYPE type = ERROR_GLYPH;
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		type = glyph->getType();
	
	return type;
}

vector<DrawInstruction> ActivityDiagram::getDrawInstructions(int id)
{
	vector<DrawInstruction> drawInstructions;
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		drawInstructions = glyph->getDrawInstructions();

	return drawInstructions;
}

string ActivityDiagram::getGlyphText(int id)
{
	string text = "";
	Glyph *glyph = getGlyphById(id);
	if (glyph != NULL)
		text = glyph->getText();

	return text;
}

bool ActivityDiagram::canRedo()
{
	return _commandManager.canRedo();
}

bool ActivityDiagram::canUndo()
{
	return _commandManager.canUndo();
}

vector<int> ActivityDiagram::getSelectedGlyphIds()
{
	vector<int> selectedGlyphIds;
	for (unsigned int i = 0; i < _glyphs.size(); i++)
		if (_glyphs[i]->isSelected())
			selectedGlyphIds.push_back(_glyphs[i]->getId());

	return selectedGlyphIds;
}

void ActivityDiagram::saveFile(string fileName)
{
	ofstream fout(fileName);
	if (fout)
	{
		vector<string> glyphLines, connectionLines;
		SaveGlyphVisitor visitor(&glyphLines, &connectionLines);
		for (unsigned int i = 0; i < _glyphs.size(); i++)
		{
			_glyphs[i]->accept(&visitor);
		}
		writeFile(&fout, glyphLines);
		fout << endl;
		writeFile(&fout, connectionLines);
	}
}

void ActivityDiagram::writeFile(ofstream *fout, vector<string> lines)
{
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		(*fout) << lines[i] << endl;
	}
}

void ActivityDiagram::layoutGlyphs()
{
	LayoutGLyphVisitor *visitor = new LayoutGLyphVisitor();
	for (unsigned int i = 0; i < _glyphs.size(); i++)
	{
		_glyphs[i]->accept(visitor);
	}
	visitor->layout();
	delete visitor;
	notify();
}

void ActivityDiagram::copy()
{
	deleteCopyGlyphsMemory();

	//map<sample, clone>
	map<Glyph*, Glyph*> glyphMap;
	// �ƻs
	vector<Glyph*> sampleGlyphs = getSelectedGlyphs();
	for (unsigned int i = 0; i < sampleGlyphs.size(); i++)
	{
		Glyph *glyphClone = sampleGlyphs[i]->clone();
		_copyGlyphs.push_back(glyphClone);
		glyphMap.insert(pair<Glyph*, Glyph*>(sampleGlyphs[i], glyphClone));
	}
	connectCopyGlyph(_copyGlyphs, glyphMap);

	notify();
}

void ActivityDiagram::cut()
{
	copy();

	vector<int> selectedGlyphs = getSelectedGlyphIds();
	for (unsigned int i = 0; i < selectedGlyphs.size(); i++)
	{
		deleteGlyph(selectedGlyphs[i]);
	}

	notify();
}

void ActivityDiagram::paste()
{
	//map<sample, clone>
	map<Glyph*, Glyph*> glyphMap;
	// �s�W
	for (unsigned int i = 0; i < _copyGlyphs.size(); i++)
	{
		int id = _idCount;
		_idCount++;
		Glyph *glyphClone = addGlyph(id, _copyGlyphs[i]->getType(), _copyGlyphs[i]->getText());
		glyphClone->setWidth(_copyGlyphs[i]->getWidth());
		glyphClone->setHeight(_copyGlyphs[i]->getHeight());
		if (glyphClone->getType() == EDGE)
		{
			glyphClone->setWidth(glyphClone->getWidth() + DELTA_X);
			glyphClone->setHeight(glyphClone->getHeight() + DELTA_Y);
		}
		glyphClone->setX(_copyGlyphs[i]->getX() + DELTA_X);
		glyphClone->setY(_copyGlyphs[i]->getY() + DELTA_Y);
		glyphMap.insert(pair<Glyph*, Glyph*>(_copyGlyphs[i], glyphClone));
	}
	connectCopyGlyph(_copyGlyphs, glyphMap);

	notify();
}

void ActivityDiagram::connectCopyGlyph(vector<Glyph*> sampleGlyphs, map<Glyph*, Glyph*> glyphMap)
{
	for (map<Glyph*, Glyph*>::iterator sampleIt = glyphMap.begin(); sampleIt != glyphMap.end(); sampleIt++)
	{
		Glyph *souceGlyphClone = glyphMap.find(sampleIt->first)->second;

		vector<Glyph*> targetGlyphsSample = sampleIt->first->getTargets();
		for (unsigned int j = 0; j < targetGlyphsSample.size(); j++)
		{
			map<Glyph*, Glyph*>::iterator targetIt = glyphMap.find(targetGlyphsSample[j]);
			if (targetIt != glyphMap.end())
			{
				Glyph *targetGlyphClone = targetIt->second;
				souceGlyphClone->connectTo(targetGlyphClone);
			}
		}
	}
}

bool ActivityDiagram::canPaste()
{
	return _copyGlyphs.size() == 0 ? false : true;
}