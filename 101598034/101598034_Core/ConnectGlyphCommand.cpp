#include "ConnectGlyphCommand.h"

ConnectGlyphCommand::ConnectGlyphCommand(ActivityDiagram *activityDiagram, int fromId, int toId)
{
	_activityDiagram = activityDiagram;
	_fromId = fromId;
	_toId = toId;
}

ConnectGlyphCommand::~ConnectGlyphCommand(void)
{
}

void ConnectGlyphCommand::execute()
{
	_activityDiagram->connectGlyph(_fromId, _toId);
}

void ConnectGlyphCommand::unexecute()
{
	_activityDiagram->deleteConnection(_fromId, _toId);
}