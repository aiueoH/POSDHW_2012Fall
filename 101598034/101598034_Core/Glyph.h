#ifndef GLYPH_H_
#define GLYPH_H_

#include "Tool.h"
class Glyph;
struct DrawInstruction;
struct GlyphProperty;
#include "GlyphVisitor.h"

#include <string>
#include <vector>

using namespace std;


class Glyph
{
public:
private:
	// basic
	int _id;
	GLYPH_TYPE _type;
	string _text;

	// GUI
	int _x, _y, _width, _height;
	bool _isSelected, _hasConnectionPoint;

protected:
	DrawInstruction createDrawLineInstruction(int fromX, int fromY, int toX, int toY);
	DrawInstruction createDrawEllipseInstruction(int x, int y, int width, int height);
	DrawInstruction createDrawRoundedRectInstruction(int x, int y, int width, int height, int xRound, int yRound);
	DrawInstruction createDrawTextInstruction(int x, int y, int width, int height, string text);
	DrawInstruction createSetColorInstruction(DRAW_INSTRUCTION_PEN_STYLE color);
	DrawInstruction createSetBrushInstruction(DRAW_INSTRUCTION_PEN_STYLE color);

public:
	Glyph(int id, GLYPH_TYPE type, string text);
	virtual ~Glyph(void) = 0;

	GlyphProperty getProperties();
	int getId();
	GLYPH_TYPE getType();
	virtual string getTypeName() = 0;
	string getText();
	virtual vector<Glyph*> getSources() = 0;
	virtual vector<Glyph*> getTargets() = 0;
	virtual vector<int> getSourceIds() = 0;
	virtual vector<int> getTargetIds() = 0;
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void setId(int value);
	void setText(string text);
	virtual void setX(int x);
	virtual void setY(int y);
	virtual void setWidth(int width);
	virtual void setHeight(int height);
	void setHasConnectionPoint(bool has);

	bool isSelected();
	void isSelected(bool is);
	bool hasConnectionPoint();
	virtual bool isOnGyph(int x, int y) = 0;
	virtual bool isOnTargetConnectionPoint(int x, int y) = 0;
	virtual bool isOnSourceConnectionPoint(int x, int y) = 0;
	bool isLonely();

	virtual bool removeSource(Glyph *glyph) = 0;
	virtual bool removeTarget(Glyph *glyph) = 0;

	virtual bool connectTo(Glyph *glyph) = 0;
	virtual bool beConnectedFrom(Glyph *glyph) = 0;
	virtual bool canAddSource(Glyph *glyph) = 0;
	virtual bool canAddTarget(Glyph *glyph) = 0;

	static string typeEnumToString(GLYPH_TYPE type);

	virtual vector<DrawInstruction> getDrawInstructions() = 0;

	virtual void accept(GlyphVisitor *glyphVisitor) = 0;

	virtual Glyph* clone() = 0;
};

struct GlyphProperty
{
	int id;
	GLYPH_TYPE type;
	string text, typeName;
	int x, y, width, height;
	bool isSelected, hasConnectionPoint;
	vector<Glyph*> sources, targets;
	vector<int> sourceIds, targetIds;

	GlyphProperty()
	{
		id = -1;
		type = ERROR_GLYPH;
		typeName = "ERROR";
		text = "";
		x = 0;
		y = 0;
		width = 0;
		height = 0;
		isSelected = false;
		hasConnectionPoint = false;
	}
};

struct DrawInstructionParameter
{
	int data;
	string text;
	DrawInstructionParameter(int d) {data = d;};
	DrawInstructionParameter(string t) {text = t;}
};

struct DrawInstruction
{
	DRAW_INSTRUCTION_TYPE type;
	vector<DrawInstructionParameter> parameters;
};

#endif