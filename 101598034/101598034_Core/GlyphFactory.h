#ifndef GLYPHFACTORY_H_
#define GLYPHFACTORY_H_
#include "Glyph.h"
#include "InitialNode.h"
#include "FinalNode.h"
#include "Edge.h"
#include "DecisionNode.h"
#include "Activity.h"
#include "Globle.h"

#include <map>

class GlyphFactory
{
private:
	// 各種 type 對應的 function
	typedef Glyph* (*NEW_GLYPH_FUNCTION)(int, string);
	static void initialMap(map<GLYPH_TYPE, NEW_GLYPH_FUNCTION> *map);
	
	static Glyph* newActivity(int id, string text);
	static Glyph* newEdge(int id, string text);
	static Glyph* newInitialNode(int id, string text);
	static Glyph* newFinalNode(int id, string text);
	static Glyph* newDecisionNode(int id, string text);
public:
	GlyphFactory(void);
	~GlyphFactory(void);

	static Glyph* createGlyph(int id, GLYPH_TYPE type, string text);
};

#endif