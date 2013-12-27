#ifndef GLYPHVISITOR_H_
#define GLYPHVISITOR_H_

class Activity;
class InitialNode;
class FinalNode;
class DecisionNode;
class Edge;

class GlyphVisitor
{
public:
	GlyphVisitor(void);
	virtual ~GlyphVisitor(void);

	virtual void visit(Activity *activity) = 0;
	virtual void visit(InitialNode *initialNode) = 0;
	virtual void visit(FinalNode *finalNode) = 0;
	virtual void visit(DecisionNode *decisionNode) = 0;
	virtual void visit(Edge *edge) = 0;

	virtual void endVisit();
};

#endif