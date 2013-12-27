#include "InitialNode.h"

InitialNode::InitialNode(int id, string text):GlyphComponent(id, INITIAL_NODE, text)
{
}

InitialNode::~InitialNode(void)
{
}

bool InitialNode::canAddSource(Glyph *glyph)
{
	return false;
}

bool InitialNode::canAddTarget(Glyph *glyph)
{
	if (glyph->getType() == EDGE) // 是Edge才可連結
	{
		if (isTargetsEmpty()) // 目前沒有任何連結才可以，InitinalNode只允許一個target
		{
			return true;
		}
	} 
	return false;
}

bool InitialNode::isOnGyph(int x, int y)
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

vector<DrawInstruction> InitialNode::getDrawInstructions()
{
	int x = getX();
	int y = getY();
	int w = getWidth();
	int h = getHeight();
	vector<DrawInstruction> drawInstructions;
	drawInstructions.push_back(createSetColorInstruction(BLACK));
	drawInstructions.push_back(createSetBrushInstruction(BLACK));
	drawInstructions.push_back(createDrawEllipseInstruction(x, y, w, h));
	
	if (isSelected())
		drawInstructions = Tool::mergeVector(drawInstructions, getDrawFrameInstruction());

	return drawInstructions;
}

string InitialNode::getTypeName()
{
	return INITIAL_NODE_TYPE_NAME;
}

void InitialNode::accept(GlyphVisitor *glyphVisitor)
{
	glyphVisitor->visit(this);
}

Glyph* InitialNode::clone()
{
	Glyph* glyph = new InitialNode(getId(), getText());
	glyph->setWidth(getWidth());
	glyph->setHeight(getHeight());
	glyph->setX(getX());
	glyph->setY(getY());
	return glyph;
}