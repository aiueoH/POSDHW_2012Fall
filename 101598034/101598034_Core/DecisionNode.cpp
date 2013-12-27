#include "DecisionNode.h"

DecisionNode::DecisionNode(int id, string text):GlyphComponent(id, DECISION_NODE, text)
{
}

DecisionNode::~DecisionNode(void)
{
}

bool DecisionNode::canAddSource(Glyph *glyph)
{
	if (glyph->getType() == EDGE) // 是Edge才可連結
		if (!isConnected(glyph))
			return true;
	return false;
}

bool DecisionNode::canAddTarget(Glyph *glyph)
{
	if (glyph->getType() == EDGE) // 是Edge才可連結
		if (!isConnected(glyph))
			return true;
	return false;
}

bool DecisionNode::isOnGyph(int x, int y)
{
	if (x >= getX() &&
		x <= getX() + getWidth() &&
		y >= getY() &&
		y <= getY() + getHeight())
	{
		return true;
	}
	return false;
}

vector<DrawInstruction> DecisionNode::getDrawInstructions()
{
	int x = getX();
	int y = getY();
	int w = getWidth();
	int h = getHeight();
	vector<DrawInstruction> drawInstructions;
	drawInstructions.push_back(createSetColorInstruction(BLACK));
	drawInstructions.push_back(createSetBrushInstruction(BLACK));
	drawInstructions.push_back(createDrawLineInstruction(x + w / 2, y, x, y + h / 2));
	drawInstructions.push_back(createDrawLineInstruction(x, y + h / 2, x + w / 2, y + h));
	drawInstructions.push_back(createDrawLineInstruction(x + w / 2, y + h, x + w, y + h / 2));
	drawInstructions.push_back(createDrawLineInstruction(x + w, y + h / 2, x + w / 2, y));
	
	if (isSelected())
		drawInstructions = Tool::mergeVector(drawInstructions, getDrawFrameInstruction());
	
	return drawInstructions;
}

string DecisionNode::getTypeName()
{
	return DECISION_NODE_TYPE_NAME;
}

void DecisionNode::accept(GlyphVisitor *glyphVisitor)
{
	glyphVisitor->visit(this);
}

Glyph* DecisionNode::clone()
{
	Glyph* glyph = new DecisionNode(getId(), getText());
	glyph->setWidth(getWidth());
	glyph->setHeight(getHeight());
	glyph->setX(getX());
	glyph->setY(getY());
	return glyph;
}