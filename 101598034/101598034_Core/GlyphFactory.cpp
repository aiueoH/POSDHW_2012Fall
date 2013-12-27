#include "GlyphFactory.h"

GlyphFactory::GlyphFactory(void)
{
}

GlyphFactory::~GlyphFactory(void)
{
}

void GlyphFactory::initialMap(map<GLYPH_TYPE, NEW_GLYPH_FUNCTION> *typeMappingFunction)
{
	typeMappingFunction->insert(pair<GLYPH_TYPE, NEW_GLYPH_FUNCTION>(ACTIVITY, &GlyphFactory::newActivity));
	typeMappingFunction->insert(pair<GLYPH_TYPE, NEW_GLYPH_FUNCTION>(EDGE, &GlyphFactory::newEdge));
	typeMappingFunction->insert(pair<GLYPH_TYPE, NEW_GLYPH_FUNCTION>(INITIAL_NODE, &GlyphFactory::newInitialNode));
	typeMappingFunction->insert(pair<GLYPH_TYPE, NEW_GLYPH_FUNCTION>(FINAL_NODE, &GlyphFactory::newFinalNode));
	typeMappingFunction->insert(pair<GLYPH_TYPE, NEW_GLYPH_FUNCTION>(DECISION_NODE, &GlyphFactory::newDecisionNode));
}

Glyph* GlyphFactory::createGlyph(int id, GLYPH_TYPE type, string text)
{
	string typeName = string(CHAR_TO_STRING_LENTH, (GLYPH_TYPE)type); // 將 type(enum) 轉為 typeName(string)
	map<GLYPH_TYPE, NEW_GLYPH_FUNCTION> typeMappingFunction; // 透過 map 取代 switch
	initialMap(&typeMappingFunction);
	return typeMappingFunction[type](id, text);
}

Glyph* GlyphFactory::newActivity(int id, string text)
{
	return new Activity(id, text);
}

Glyph* GlyphFactory::newEdge(int id, string text)
{
	return new Edge(id, text);
}

Glyph* GlyphFactory::newInitialNode(int id, string text)
{
	return new InitialNode(id, text);
}

Glyph* GlyphFactory::newFinalNode(int id, string text)
{
	return new FinalNode(id, text);
}

Glyph* GlyphFactory::newDecisionNode(int id, string text)
{
	return new DecisionNode(id, text);
}