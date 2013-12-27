#include "Edge.h"

Edge::Edge(int id, string text):Glyph(id, EDGE, text)
{
	_target = NULL;
	_source = NULL;
}

Edge::~Edge(void)
{
}

bool Edge::connectTo(Glyph *glyph)
{
	if (canAddTarget(glyph) && glyph->canAddSource(this)) // 判斷可以連線至target以及target可以被自己連結
	{
		_target = glyph; // 將target加入vector內
		glyph->beConnectedFrom(this); // 叫target將自自己加入source
		setWidth(0);
		setHeight(0);
		return true;
	}
	return false;
}

bool Edge::beConnectedFrom(Glyph *glyph)
{
	if (canAddSource(glyph))
	{
		_source = glyph;
		setX(0);
		setY(0);
		return true;
	}
	return false;
}

bool Edge::canAddSource(Glyph *glyph)
{
	if (glyph->getType() != EDGE) // 是Edge才可連結
		if (_source == NULL) // 目前沒有連線
			return true;
	return false;
}

bool Edge::canAddTarget(Glyph *glyph)
{
	if (glyph->getType() != EDGE) // 是Edge才可連結
		if (_target == NULL) // 目前沒有連線
			return true;
	return false;
}

vector<Glyph*> Edge::getSources()
{
	vector<Glyph*> sources;
	if (_source != NULL)
		sources.push_back(_source);
	return sources;
}

vector<Glyph*> Edge::getTargets()
{
	vector<Glyph*> targets;
	if (_target != NULL)
		targets.push_back(_target);
	return targets;
}

vector<int> Edge::getSourceIds()
{
	vector<int> ids;
	if (_source != NULL)
		ids.push_back(_source->getId());
	return ids;
}

vector<int> Edge::getTargetIds()
{
	vector<int> ids;
	if (_target != NULL)
		ids.push_back(_target->getId());
	return ids;
}

bool Edge::removeSource(Glyph *glyph)
{
	if (_source == glyph)
	{
		_source = NULL;
		return true;
	}
	return false;
}

bool Edge::removeTarget(Glyph *glyph)
{
	if (_target == glyph)
	{
		_target = NULL;
		return true;
	}
	return false;
}

bool Edge::isOnGyph(int x, int y)
{
	int fromX = (getWidth() > getX()) ? getX() : getWidth();
	int toX =  (getWidth() > getX()) ? getWidth() : getX();
	int fromY = (getWidth() > getX()) ? getY() : getHeight();
	int toY =  (getWidth() > getX()) ? getHeight() : getY();

	double deltaX = toX - fromX, deltaY = toY - fromY;
	double standard = (deltaX > deltaY) ? deltaX : deltaY;
	double stepX = deltaX / standard, stepY = deltaY / standard;

	int i = 0;
	while (i++ <= standard)
	{
		double nowX = fromX + stepX * i;
		double nowY = fromY + stepY * i;
		if (x >= nowX - EDGE_COLLISION_SIZR && 
			x <= nowX + EDGE_COLLISION_SIZR && 
			y >= nowY - EDGE_COLLISION_SIZR && 
			y <= nowY + EDGE_COLLISION_SIZR)
			return true;
	}

	return false;
}

bool Edge::isOnTargetConnectionPoint(int x, int y)
{
	if (x >= getWidth() &&
		x <= getWidth() + EDGE_CONNECTION_POINT_WIDTH &&
		y >= getHeight() - EDGE_CONNECTION_POINT_HEIGHT / 2&&
		y <= getHeight() + EDGE_CONNECTION_POINT_HEIGHT / 2)
	{
		return true;
	}
	return false;
}

bool Edge::isOnSourceConnectionPoint(int x, int y)
{
	if (x >= getX() - EDGE_CONNECTION_POINT_WIDTH &&
		x <= getX() &&
		y >= getY() - EDGE_CONNECTION_POINT_HEIGHT / 2&&
		y <= getY() + EDGE_CONNECTION_POINT_HEIGHT / 2)
	{
		return true;
	}
	return false;
}

vector<DrawInstruction> Edge::getDrawInstructions()
{
	int fromX = getX();
	int fromY = getY();
	int toX = getWidth();
	int toY = getHeight();
	string text = getText();
	int textWidth = text.length() * TEXT_LENGTH_PER_CHAR;
	int textHeight = GRAPH_HEIGHT;
	int textX = (fromX + toX) / 2 - textWidth / 2;
	int textY = (fromY + toY) / 2;
	vector<DrawInstruction> drawInstructions;
	drawInstructions.push_back(createSetColorInstruction(BLACK));
	drawInstructions.push_back(createSetBrushInstruction(BLACK));
	drawInstructions.push_back(createDrawLineInstruction(fromX, fromY, toX, toY));
	drawInstructions.push_back(createDrawLineInstruction(toX, toY, toX - EDGE_ARROW_LENGTH, toY - EDGE_ARROW_LENGTH));
	drawInstructions.push_back(createDrawLineInstruction(toX, toY, toX - EDGE_ARROW_LENGTH, toY + EDGE_ARROW_LENGTH));
	drawInstructions.push_back(createDrawTextInstruction(textX, textY, textWidth, textHeight, text));

	if (isSelected())
		drawInstructions = Tool::mergeVector(drawInstructions, getDrawFrameInstruction());
	if (hasConnectionPoint())
		drawInstructions = Tool::mergeVector(drawInstructions, getDrawConnectionPointInstruction());

	return drawInstructions;
}

vector<DrawInstruction> Edge::getDrawFrameInstruction()
{
	int fromX = getX();
	int fromY = getY();
	int toX = getWidth();
	int toY = getHeight();
	string text = getText();
	int textWidth = text.length() * TEXT_LENGTH_PER_CHAR;
	int textHeight = GRAPH_HEIGHT;
	int textX = (fromX + toX) / 2 - textWidth / 2;
	int textY = (fromY + toY) / 2;
	vector<DrawInstruction> drawInstructions;
	drawInstructions.push_back(createSetColorInstruction(BLUE));
	drawInstructions.push_back(createSetBrushInstruction(BLUE));
	drawInstructions.push_back(createDrawLineInstruction(fromX, fromY, toX, toY));
	drawInstructions.push_back(createDrawLineInstruction(toX, toY, toX - EDGE_ARROW_LENGTH, toY - EDGE_ARROW_LENGTH));
	drawInstructions.push_back(createDrawLineInstruction(toX, toY, toX - EDGE_ARROW_LENGTH, toY + EDGE_ARROW_LENGTH));
	drawInstructions.push_back(createDrawTextInstruction(textX, textY, textWidth, textHeight, text));
	
	return drawInstructions;
}

vector<DrawInstruction> Edge::getDrawConnectionPointInstruction()
{
	int targetX = getWidth();
	int targetY = getHeight() - EDGE_CONNECTION_POINT_HEIGHT / 2;
	int sourceX = getX() - EDGE_CONNECTION_POINT_WIDTH;
	int sourceY = getY() - EDGE_CONNECTION_POINT_HEIGHT / 2;
	vector<DrawInstruction> drawInstructions;
	drawInstructions.push_back(createSetColorInstruction(BLACK));
	drawInstructions.push_back(createSetBrushInstruction(GRAY));
	drawInstructions.push_back(createDrawRoundedRectInstruction(targetX, targetY, EDGE_CONNECTION_POINT_WIDTH, EDGE_CONNECTION_POINT_HEIGHT, 0, 0));
	drawInstructions.push_back(createDrawRoundedRectInstruction(sourceX, sourceY, EDGE_CONNECTION_POINT_WIDTH, EDGE_CONNECTION_POINT_HEIGHT, 0, 0));

	return drawInstructions;
}

void Edge::setX(int x)
{
	if (_source != NULL)
		x = _source->getX() + _source->getWidth();
	Glyph::setX(x);
}

void Edge::setY(int y)
{
	if (_source != NULL)
		y = _source->getY() + _source->getHeight() / 2;
	Glyph::setY(y);
}

void Edge::setWidth(int width)
{
	if (_target != NULL)
		width = _target->getX();
	Glyph::setWidth(width);
}

void Edge::setHeight(int height)
{
	if (_target != NULL)
		height = _target->getY() + _target->getHeight() / 2;
	Glyph::setHeight(height);
}

string Edge::getTypeName()
{
	return EDGE_TYPE_NAME;
}

void Edge::accept(GlyphVisitor *glyphVisitor)
{
	glyphVisitor->visit(this);
}

Glyph* Edge::clone()
{
	Glyph* glyph = new Edge(getId(), getText());
	glyph->setWidth(getWidth());
	glyph->setHeight(getHeight());
	glyph->setX(getX());
	glyph->setY(getY());
	return glyph;
}