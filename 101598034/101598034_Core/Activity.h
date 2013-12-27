#ifndef ACTIVITY_H_
#define ACTIVITY_H_

#include "Globle.h"
#include "Glyphcomponent.h"

class Activity :
	public GlyphComponent
{
public:
	Activity(int id, string text);
	~Activity(void);

	bool canAddSource(Glyph *glyph);
	bool canAddTarget(Glyph *glyph);

	bool isOnGyph(int x, int y);

	vector<DrawInstruction> getDrawInstructions();
	string getTypeName();

	void accept(GlyphVisitor *glyphVisitor);

	Glyph* clone();
};

#endif