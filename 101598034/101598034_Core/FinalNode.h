#ifndef FINALNODE_H_
#define FINALNODE_H_

#include "Globle.h"
#include "GlyphComponent.h"

class FinalNode :
	public GlyphComponent
{
public:
	FinalNode(int id, string text);
	~FinalNode(void);
	
	bool canAddSource(Glyph *glyph);
	bool canAddTarget(Glyph *glyph);

	bool isOnGyph(int x, int y);

	vector<DrawInstruction> getDrawInstructions();
	string getTypeName();

	void accept(GlyphVisitor *glyphVisitor);

	Glyph* clone();
};

#endif