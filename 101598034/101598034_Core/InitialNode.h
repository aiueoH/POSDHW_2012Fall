#ifndef INITIALNODE_H_
#define INITIALNODE_H_

#include "Globle.h"
#include "GlyphComponent.h"

class InitialNode :
	public GlyphComponent
{
public:
	InitialNode(int id, string text);
	~InitialNode(void);

	bool canAddSource(Glyph *glyph);
	bool canAddTarget(Glyph *glyph);

	bool isOnGyph(int x, int y);

	vector<DrawInstruction> getDrawInstructions();
	string getTypeName();

	void accept(GlyphVisitor *glyphVisitor);

	Glyph* clone();
};

#endif
