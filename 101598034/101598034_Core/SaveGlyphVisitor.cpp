#include "SaveGlyphVisitor.h"

SaveGlyphVisitor::SaveGlyphVisitor(vector<string> *glyphLines, vector<string> *connectionLines)
{
	_glyphLines = glyphLines;
	_connectionLines = connectionLines;
}

SaveGlyphVisitor::~SaveGlyphVisitor(void)
{
}

void SaveGlyphVisitor::visit(Activity *activity)
{
	record(activity);
}

void SaveGlyphVisitor::visit(InitialNode *initialNode)
{
	record(initialNode);
}

void SaveGlyphVisitor::visit(FinalNode *finalNode)
{
	record(finalNode);
}

void SaveGlyphVisitor::visit(DecisionNode *decisionNode)
{
	record(decisionNode);
}

void SaveGlyphVisitor::visit(Edge *edge)
{
	record(edge);
}

void SaveGlyphVisitor::record(Glyph *glyph)
{
	_glyphLines->push_back(createGlyphLine(glyph->getType(), glyph->getText()));
	vector<int> ids = glyph->getTargetIds();
	if (ids.size() > 0)
	{
		for (unsigned int i = 0; i < ids.size(); i++)
		{
			_connectionLines->push_back(createConnectionLine(glyph->getId(), ids[i]));
		}
	}
}

string SaveGlyphVisitor::createGlyphLine(GLYPH_TYPE type, string text)
{
	string line = "";
	line += Tool::charToString(type);
	if (text != "")
	{
		line += ", " + text;
	}
	return line;
}

string SaveGlyphVisitor::createConnectionLine(int id, int targetId)
{
	string line = "";
	line += Tool::intToString(id) + "," + Tool::intToString(targetId);
	return line;
}