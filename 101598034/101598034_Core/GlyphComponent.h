#ifndef GLYPHCOMPONENT_H_
#define GLYPHCOMPONENT_H_

#include "Globle.h"
#include "Glyph.h"

#include <vector>

class GlyphComponent :
	public Glyph
{
private:
	vector<Glyph*> _sources, _targets;
	void reSetEdgePosition();

protected:
	vector<DrawInstruction> getDrawFrameInstruction();

public:
	GlyphComponent(int id, GLYPH_TYPE type, string text);
	~GlyphComponent(void) = 0;
	
	bool connectTo(Glyph *glyph);
	bool beConnectedFrom(Glyph *glyph);
	virtual bool canAddSource(Glyph *glyph) = 0;
	virtual bool canAddTarget(Glyph *glyph) = 0;

	vector<Glyph*> getSources();
	vector<Glyph*> getTargets();
	vector<int> getSourceIds();
	vector<int> getTargetIds();
	virtual string getTypeName() = 0;

	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);

	bool removeSource(Glyph *glyph);
	bool removeTarget(Glyph *glyph);

	bool isSourcesEmpty();
	bool isTargetsEmpty();
	bool isConnected(Glyph *glyph);
	virtual bool isOnGyph(int x, int y) = 0;
	bool isOnTargetConnectionPoint(int x, int y);
	bool isOnSourceConnectionPoint(int x, int y);

	virtual vector<DrawInstruction> getDrawInstructions() = 0;

	virtual void accept(GlyphVisitor *glyphVisitor) = 0;

	virtual Glyph* clone() = 0;
};

#endif