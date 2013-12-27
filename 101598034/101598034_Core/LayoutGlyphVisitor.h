#ifndef LAYOUTGLYPHVISITOR_H_
#define LAYOUTGLYPHVISITOR_H_

#include "GlyphVisitor.h"
#include "Tool.h"
#include "Activity.h"
#include "InitialNode.h"
#include "FinalNode.h"
#include "DecisionNode.h"
#include "Edge.h"
#include "Glyph.h"

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class LayoutGLyphVisitor :
	public GlyphVisitor
{
private:
	vector<Glyph*> _glyphs;

	void layoutEdges();
	void layoutComponents(Glyph *glyph,vector<Glyph*> *computedGlyphs, vector<int> *postionLevel, unsigned int depth);
	bool isVisited(Glyph *glyph, vector<Glyph*> *visitedGlyphs);

public:
	LayoutGLyphVisitor();
	~LayoutGLyphVisitor(void);	
	
	void visit(Activity *activity);
	void visit(InitialNode *initialNode);
	void visit(FinalNode *finalNode);
	void visit(DecisionNode *decisionNode);
	void visit(Edge *edge);
	
	void layout();
};

#endif