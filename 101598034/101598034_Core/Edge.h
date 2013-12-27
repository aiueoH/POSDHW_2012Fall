#ifndef EDGE_H_
#define EDGE_H_

#include "Globle.h"
#include "Glyph.h"
#include "Tool.h"

class Edge :
	public Glyph
{
private:
	Glyph *_source, *_target;
	vector<DrawInstruction> getDrawFrameInstruction();
	vector<DrawInstruction> getDrawConnectionPointInstruction();

public:
	Edge(int id, string text);
	~Edge(void);

	bool connectTo(Glyph *glyph);
	bool beConnectedFrom(Glyph *glyph);
	bool canAddSource(Glyph *glyph);
	bool canAddTarget(Glyph *glyph);

	vector<Glyph*> getSources();
	vector<Glyph*> getTargets();
	vector<int> getSourceIds();
	vector<int> getTargetIds();
	string getTypeName();

	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);

	bool removeSource(Glyph *glyph);
	bool removeTarget(Glyph *glyph);

	bool isOnGyph(int x, int y);
	bool isOnTargetConnectionPoint(int x, int y);
	bool isOnSourceConnectionPoint(int x, int y);

	vector<DrawInstruction> getDrawInstructions();

	void accept(GlyphVisitor *glyphVisitor);

	Glyph* clone();
};

#endif