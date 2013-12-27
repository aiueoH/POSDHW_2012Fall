#include "Activity.h"

Activity::Activity(int id, string text):GlyphComponent(id, ACTIVITY, text)
{
	setWidth(text.length() * TEXT_LENGTH_PER_CHAR);
}

Activity::~Activity(void)
{
}

bool Activity::canAddSource(Glyph *glyph)
{
	if (glyph->getType() == EDGE) // 是Edge才可連結
		if (!isConnected(glyph))
			return true;
	return false;
}

bool Activity::canAddTarget(Glyph *glyph)
{
	if (glyph->getType() == EDGE) // 是Edge才可連結
		if (getTargets().empty())
			return true;
	return false;
}

bool Activity::isOnGyph(int x, int y)
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

vector<DrawInstruction> Activity::getDrawInstructions()
{
	int x = getX();
	int y = getY();
	int w = getWidth();
	int h = getHeight();
	int xRound = ACTIVITY_REC_X_ROUND;
	int yRound = ACTIVITY_REC_Y_ROUND;
	string text = getText();
	vector<DrawInstruction> drawInstructions;
	drawInstructions.push_back(createSetColorInstruction(BLACK));
	drawInstructions.push_back(createSetBrushInstruction(NOBRUSH));
	drawInstructions.push_back(createDrawRoundedRectInstruction(x, y, w, h, xRound, yRound));
	drawInstructions.push_back(createSetBrushInstruction(BLACK));
	drawInstructions.push_back(createDrawTextInstruction(x + ACTIVITY_TEXT_PADDING, y + ACTIVITY_TEXT_PADDING, w - ACTIVITY_TEXT_PADDING * 2, h - ACTIVITY_TEXT_PADDING * 2, text));

	if (isSelected())
		drawInstructions = Tool::mergeVector(drawInstructions, getDrawFrameInstruction());
	
	return drawInstructions;
}

string Activity::getTypeName()
{
	return ACTIVITY_TYPE_NAME;
}

void Activity::accept(GlyphVisitor *glyphVisitor)
{
	glyphVisitor->visit(this);
}

Glyph* Activity::clone()
{
	Glyph* glyph = new Activity(getId(), getText());
	glyph->setWidth(getWidth());
	glyph->setHeight(getHeight());
	glyph->setX(getX());
	glyph->setY(getY());
	return glyph;
}