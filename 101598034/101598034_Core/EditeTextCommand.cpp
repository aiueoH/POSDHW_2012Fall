#include "EditTextCommand.h"

EditTextCommand::EditTextCommand(ActivityDiagram *activityDiagram, int id, string text)
{
	_activityDiagram = activityDiagram;
	_id = id;
	_text = text;
	_originalText = activityDiagram->getGlyphText(id);
}

EditTextCommand::~EditTextCommand(void)
{
}

void EditTextCommand::execute()
{
	_activityDiagram->setGlyphText(_id, _text);
}

void EditTextCommand::unexecute()
{
	_activityDiagram->setGlyphText(_id, _originalText);
}