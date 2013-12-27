#ifndef SAVEGLYPHVISITOR_H_
#define SAVEGLYPHVISITOR_H_

#include "Glyphvisitor.h"
#include "Tool.h"
#include "Activity.h"
#include "InitialNode.h"
#include "FinalNode.h"
#include "DecisionNode.h"
#include "Edge.h"
#include "Glyph.h"

#include <string>
#include <vector>

using namespace std;

class SaveGlyphVisitor :
	public GlyphVisitor
{
private :
	vector<string> *_glyphLines, *_connectionLines;

	void record(Glyph *glyph);
	string createGlyphLine(GLYPH_TYPE type, string text);
	string createConnectionLine(int id, int targetId);

public:
	SaveGlyphVisitor(vector<string> *glyphLines, vector<string> *connectionLines);
	~SaveGlyphVisitor(void);

	void visit(Activity *activity);
	void visit(InitialNode *initialNode);
	void visit(FinalNode *finalNode);
	void visit(DecisionNode *decisionNode);
	void visit(Edge *edge);
};

#endif