#include "GlyphComponent.h"

GlyphComponent::GlyphComponent(int id, GLYPH_TYPE type, string text):Glyph(id, type, text)
{
}

GlyphComponent::~GlyphComponent(void)
{
}

bool GlyphComponent::connectTo(Glyph *glyph)
{
	if (canAddTarget(glyph) && glyph->canAddSource(this)) // 判斷可以連線至target以及target可以被自己連結
	{
		_targets.push_back(glyph); // 將target加入vector內
		glyph->beConnectedFrom(this); // 叫target將自自己加入source
		return true;
	}
	return false;
}

bool GlyphComponent::beConnectedFrom(Glyph *glyph)
{
	if (canAddSource(glyph))
	{
		_sources.push_back(glyph);
		return true;
	}
	return false;
}

/*
 * 判斷是否已存在連結
 */
bool GlyphComponent::isConnected(Glyph *glyph)
{
	for (unsigned int i = 0; i < _sources.size(); i++)
		if (glyph == _sources[i])
			return true;
	for (unsigned int i = 0; i < _targets.size(); i++)
		if (glyph == _targets[i])
			return true;
	return false;
}

bool GlyphComponent::isSourcesEmpty()
{
	return _sources.empty();
}

bool GlyphComponent::isTargetsEmpty()
{
	return _targets.empty();
}

vector<Glyph*> GlyphComponent::getSources()
{
	return _sources;
}

vector<Glyph*> GlyphComponent::getTargets()
{
	return _targets;
}

vector<int> GlyphComponent::getSourceIds()
{
	vector<int> ids;
	for (unsigned int i = 0; i < _sources.size(); i++)
	{
		ids.push_back(_sources[i]->getId());
	}
	return ids;
}

vector<int> GlyphComponent::getTargetIds()
{
	vector<int> ids;
	for (unsigned int i = 0; i < _targets.size(); i++)
	{
		ids.push_back(_targets[i]->getId());
	}
	return ids;
}


bool GlyphComponent::removeSource(Glyph *glyph)
{
	for (unsigned int i = 0; i < _sources.size(); i++)
		if (_sources[i] == glyph)
		{
			_sources.erase(_sources.begin() + i);
			return true;
		}
	return false;
}

bool GlyphComponent::removeTarget(Glyph *glyph)
{
	for (unsigned int i = 0; i < _targets.size(); i++)
		if (_targets[i] == glyph)
		{
			_targets.erase(_targets.begin() + i);
			return true;
		}
	return false;
}

vector<DrawInstruction> GlyphComponent::getDrawFrameInstruction()
{
	int x = getX();
	int y = getY();
	int w = getWidth();
	int h = getHeight();
	vector<DrawInstruction> drawInstructions;
	drawInstructions.push_back(createSetColorInstruction(BLUE));
	drawInstructions.push_back(createSetBrushInstruction(BLUE));
	drawInstructions.push_back(createDrawLineInstruction(x - 1, y - 1, x - 1, y + h + 1));
	drawInstructions.push_back(createDrawLineInstruction(x - 1, y + h + 1, x + w + 1, y + h + 1));
	drawInstructions.push_back(createDrawLineInstruction(x + w + 1, y + h + 1, x + w + 1, y - 1));
	drawInstructions.push_back(createDrawLineInstruction(x + w + 1, y - 1, x - 1, y - 1));

	return drawInstructions;
}

void GlyphComponent::reSetEdgePosition()
{
	for (unsigned int i = 0; i < _targets.size(); i++)
	{
		_targets[i]->setX(_targets[i]->getX());
		_targets[i]->setY(_targets[i]->getY());
	}
	for (unsigned int i = 0; i < _sources.size(); i++)
	{
		_sources[i]->setWidth(_sources[i]->getWidth());
		_sources[i]->setHeight(_sources[i]->getHeight());
	}
}

void GlyphComponent::setX(int x)
{
	Glyph::setX(x);
	reSetEdgePosition();
}

void GlyphComponent::setY(int y)
{
	Glyph::setY(y);
	reSetEdgePosition();
}

void GlyphComponent::setWidth(int width)
{
	Glyph::setWidth(width);
	reSetEdgePosition();
}

void GlyphComponent::setHeight(int height)
{
	Glyph::setHeight(height);
	reSetEdgePosition();
}

bool GlyphComponent::isOnTargetConnectionPoint(int x, int y)
{
	return false;
}

bool GlyphComponent::isOnSourceConnectionPoint(int x, int y)
{
	return false;
}