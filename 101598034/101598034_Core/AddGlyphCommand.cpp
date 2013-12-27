#include "AddGlyphCommand.h"

AddGlyphCommand::AddGlyphCommand(ActivityDiagram *activityDiagram, int id, GLYPH_TYPE type, string text)
{
	_activityDiagram = activityDiagram;
	_glyphProperty.id = id;
	_glyphProperty.text = text;
	_glyphProperty.type = type;

	_hasBeenExecuted = false;
}

AddGlyphCommand::~AddGlyphCommand(void)
{
}

void AddGlyphCommand::execute()
{
	_activityDiagram->addGlyph(_glyphProperty.id, _glyphProperty.type, _glyphProperty.text);
	if (_hasBeenExecuted)
		_activityDiagram->setGlyphProperty(_glyphProperty.id, _glyphProperty);
	_hasBeenExecuted = true;
}

void AddGlyphCommand::unexecute()
{
	_glyphProperty = _activityDiagram->getGlyphProperty(_glyphProperty.id);
	_activityDiagram->deleteGlyph(_glyphProperty.id);
}