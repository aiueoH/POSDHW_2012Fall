#include "Glyph.h"

Glyph::Glyph(int id, GLYPH_TYPE type, string text)
{
	_id = id;
	_type = type;
	_text = text;

	// GUI
	_x = 0;
	_y = 0;
	_width = GRAPH_WIDTH;
	_height = GRAPH_HEIGHT;
	_isSelected = false;
	_hasConnectionPoint = false;
}

Glyph::~Glyph(void)
{
}

GlyphProperty Glyph::getProperties()
{
	GlyphProperty property;
	property.id = getId();
	property.type = getType();
	property.typeName = getTypeName();
	property.text = getText();
	property.sourceIds = getSourceIds();
	property.targetIds = getTargetIds();
	property.x = getX();
	property.y = getY();
	property.height = getHeight();
	property.width = getWidth();
	property.isSelected = isSelected();
	property.hasConnectionPoint = hasConnectionPoint();

	return property;
}

int Glyph::getX()
{
	return _x;
}

int Glyph::getY()
{
	return _y;
}

int Glyph::getWidth()
{
	return _width;
}

int Glyph::getHeight()
{
	return _height;
}

bool Glyph::isSelected()
{
	return _isSelected;
}

bool Glyph::isLonely()
{
	if (getTargetIds().size() == 0 && getSourceIds().size() == 0)
	{
		return true;
	}
	return false;
}

int Glyph::getId()
{
	return _id;
}

GLYPH_TYPE Glyph::getType()
{
	return _type;
}

string Glyph::getText()
{
	return _text;
}

void Glyph::setX(int x)
{
	if (x < 0)
		x = 0;
	if (x > PANEL_WIDTH)
		x = PANEL_WIDTH;
	_x = x;
}

void Glyph::setY(int y)
{
	if (y < 0)
		y = 0;
	if (y > PANEL_HEIGHT)
		y = PANEL_HEIGHT;
	_y = y;
}

void Glyph::setWidth(int width)
{
	_width = width;
}

void Glyph::setHeight(int height)
{
	_height = height;
}

void Glyph::setHasConnectionPoint(bool has)
{
	_hasConnectionPoint = has;
}

void Glyph::isSelected(bool isSelected)
{
	_isSelected = isSelected;
}

bool Glyph::hasConnectionPoint()
{
	return _hasConnectionPoint;
}

void Glyph::setId(int id)
{
	_id = id;
}

void Glyph::setText(string text)
{
	_text = text;
}

string Glyph::typeEnumToString(GLYPH_TYPE type)
{
	return Tool::charToString((char)type);
}

DrawInstruction Glyph::createDrawLineInstruction(int fromX, int fromY, int toX, int toY)
{
	vector<DrawInstructionParameter> parameters;
	parameters.push_back(DrawInstructionParameter(fromX));
	parameters.push_back(DrawInstructionParameter(fromY));
	parameters.push_back(DrawInstructionParameter(toX));
	parameters.push_back(DrawInstructionParameter(toY));

	DrawInstruction drawInstruction;
	drawInstruction.type = DRAW_LINE;
	drawInstruction.parameters = parameters;

	return drawInstruction;
}

DrawInstruction Glyph::createDrawEllipseInstruction(int x, int y, int width, int height)
{	
	vector<DrawInstructionParameter> parameters;
	parameters.push_back(DrawInstructionParameter(x));
	parameters.push_back(DrawInstructionParameter(y));
	parameters.push_back(DrawInstructionParameter(width));
	parameters.push_back(DrawInstructionParameter(height));

	DrawInstruction drawInstruction;
	drawInstruction.type = DRAW_ELLIPSE;
	drawInstruction.parameters = parameters;

	return drawInstruction;
}

DrawInstruction Glyph::createDrawRoundedRectInstruction(int x, int y, int width, int height, int xRound, int yRound)
{	
	vector<DrawInstructionParameter> parameters;
	parameters.push_back(DrawInstructionParameter(x));
	parameters.push_back(DrawInstructionParameter(y));
	parameters.push_back(DrawInstructionParameter(width));
	parameters.push_back(DrawInstructionParameter(height));
	parameters.push_back(DrawInstructionParameter(xRound));
	parameters.push_back(DrawInstructionParameter(yRound));

	DrawInstruction drawInstruction;
	drawInstruction.type = DRAW_ROUNDEDRECT;
	drawInstruction.parameters = parameters;

	return drawInstruction;
}

DrawInstruction Glyph::createDrawTextInstruction(int x, int y, int width, int height, string text)
{
	vector<DrawInstructionParameter> parameters;
	parameters.push_back(DrawInstructionParameter(x));
	parameters.push_back(DrawInstructionParameter(y));
	parameters.push_back(DrawInstructionParameter(width));
	parameters.push_back(DrawInstructionParameter(height));
	parameters.push_back(DrawInstructionParameter(text));

	DrawInstruction drawInstruction;
	drawInstruction.type = DRAW_TEXT;
	drawInstruction.parameters = parameters;

	return drawInstruction;
}

DrawInstruction Glyph::createSetColorInstruction(DRAW_INSTRUCTION_PEN_STYLE color)
{
	vector<DrawInstructionParameter> parameters;
	parameters.push_back(DrawInstructionParameter(color));

	DrawInstruction drawInstruction;
	drawInstruction.type = SET_PEN_COLOR;
	drawInstruction.parameters = parameters;

	return drawInstruction;
}

DrawInstruction Glyph::createSetBrushInstruction(DRAW_INSTRUCTION_PEN_STYLE color)
{
	vector<DrawInstructionParameter> parameters;
	parameters.push_back(DrawInstructionParameter(color));

	DrawInstruction drawInstruction;
	drawInstruction.type = SET_BRUSH;
	drawInstruction.parameters = parameters;

	return drawInstruction;
}