#ifndef DECISIONNODE_H_
#define DECISIONNODE_H_

#include "Globle.h"
#include "Glyphcomponent.h"

class DecisionNode :
	public GlyphComponent
{
public:
	DecisionNode(int id, string text);
	~DecisionNode(void);

	bool canAddSource(Glyph *glyph);
	bool canAddTarget(Glyph *glyph);

	bool isOnGyph(int x, int y);

	vector<DrawInstruction> getDrawInstructions();
	string getTypeName();

	void accept(GlyphVisitor *glyphVisitor);

	Glyph* clone();
};

#endif