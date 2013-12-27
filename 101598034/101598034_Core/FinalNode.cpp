#include "FinalNode.h"

FinalNode::FinalNode(int id, string text):GlyphComponent(id, FINAL_NODE, text)
{
}

FinalNode::~FinalNode(void)
{
}

bool FinalNode::canAddSource(Glyph *glyph)
{
	if (glyph->getType() == EDGE) // 是Edge才可連結
		if (!isConnected(glyph))
		{
			return true;
		}
		return false;
}

bool FinalNode::canAddTarget(Glyph *glyph)
{
	return false; // FinalNode不能連出
}

bool FinalNode::isOnGyph(int x, int y)
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

vector<DrawInstruction> FinalNode::getDrawInstructions()
{
	int x = getX();
	int y = getY();
	int w = getWidth();
	int h = getHeight();
	int wInside = w * 2 / 3;
	int hInside = h * 2 / 3;
	vector<DrawInstruction> drawInstructions;
	drawInstructions.push_back(createSetColorInstruction(BLACK));
	drawInstructions.push_back(createSetBrushInstruction(NOBRUSH));
	drawInstructions.push_back(createDrawEllipseInstruction(x, y, w, h));
	drawInstructions.push_back(createSetBrushInstruction(BLACK));
	drawInstructions.push_back(createDrawEllipseInstruction(x + (w - wInside) / 2, y + (h - hInside) / 2, wInside, hInside));

	if (isSelected())
		drawInstructions = Tool::mergeVector(drawInstructions, getDrawFrameInstruction());

	return drawInstructions;
}

string FinalNode::getTypeName()
{
	return FINAL_NODE_TYPE_NAME;
}

void FinalNode::accept(GlyphVisitor *glyphVisitor)
{
	glyphVisitor->visit(this);
}

Glyph* FinalNode::clone()
{
	Glyph* glyph = new FinalNode(getId(), getText());
	glyph->setWidth(getWidth());
	glyph->setHeight(getHeight());
	glyph->setX(getX());
	glyph->setY(getY());
	return glyph;
}