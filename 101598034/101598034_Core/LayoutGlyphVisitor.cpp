#include "LayoutGLyphVisitor.h"

LayoutGLyphVisitor::LayoutGLyphVisitor()
{
}

LayoutGLyphVisitor::~LayoutGLyphVisitor(void)
{
}

void LayoutGLyphVisitor::visit(Activity *activity)
{
	_glyphs.push_back(activity);
}

void LayoutGLyphVisitor::visit(InitialNode *initialNode)
{
	_glyphs.push_back(initialNode);
}

void LayoutGLyphVisitor::visit(FinalNode *finalNode)
{
	_glyphs.push_back(finalNode);
}

void LayoutGLyphVisitor::visit(DecisionNode *decisionNode)
{
	_glyphs.push_back(decisionNode);
}

void LayoutGLyphVisitor::visit(Edge *edge)
{
	_glyphs.push_back(edge);
}

void LayoutGLyphVisitor::layoutEdges()
{
	for (unsigned int i = 0; i < _glyphs.size(); i++)
	{
		if (_glyphs[i]->getType() == EDGE)
		{
			Glyph* source = _glyphs[i]->getSources()[0];
			Glyph* target = _glyphs[i]->getTargets()[0];
			if (source != NULL)
			{
				_glyphs[i]->setX(source->getX() + source->getWidth());
				_glyphs[i]->setY(source->getY() + source->getHeight() / 2);
			}
			if (target != NULL)
			{
				_glyphs[i]->setWidth(target->getX());
				_glyphs[i]->setHeight(target->getY() + target->getHeight() / 2);
			}
		}
	}
}

void LayoutGLyphVisitor::layoutComponents(Glyph *glyph,vector<Glyph*> *computedGlyphs, vector<int> *postionLevel, unsigned int depth)
{
	// �p��� depth �ثe��ĴX�h
	if (glyph->getType() != EDGE)
	{
		if (postionLevel->size() < depth + 1) // �� depth �٨S��L
			postionLevel->push_back(0);
		else
			(*postionLevel)[depth]++; // level +1

		// �p�� position
		int blockWidth = 500, blockHeight = 200;
		int x = depth * blockWidth;
		int y = (*postionLevel)[depth] * blockHeight;
		glyph->setX(x);
		glyph->setY(y);
	}

	computedGlyphs->push_back(glyph); // �O�����X�L��Glyph

	vector<Glyph*> targetGlyphs = glyph->getTargets();
	if (targetGlyphs.size() == 0) // �S�� target �h�^�W�@��
	{
		computedGlyphs->pop_back();
		return;
	}

	for (unsigned int i = 0; i < targetGlyphs.size(); i++)
		if (!isVisited(targetGlyphs[i], computedGlyphs)) // �O�S���X�L��Glyph
		{
			if (glyph->getType() == EDGE)
				depth += 1;
			layoutComponents(targetGlyphs[i], computedGlyphs, postionLevel, depth);
		}

		computedGlyphs->pop_back(); //�h�^�W�@��Glyph
}

void LayoutGLyphVisitor::layout()
{
	vector<Glyph*> computedGlyphs; // �ΨӰO�����X�L��Glyph
	vector<int> postionLevel;
	layoutComponents(_glyphs[0], &computedGlyphs, &postionLevel, 0);
	layoutEdges();
}

bool LayoutGLyphVisitor::isVisited(Glyph *glyph, vector<Glyph*> *visitedGlyphs)
{
	if (visitedGlyphs->end() == find(visitedGlyphs->begin(), visitedGlyphs->end(), glyph)) // end == find() �N��S���M�X�L
		return false;
	return true;
}