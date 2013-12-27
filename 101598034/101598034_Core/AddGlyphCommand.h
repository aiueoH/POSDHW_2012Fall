#ifndef ADDGLYPHCOMMAND_H_
#define ADDGLYPHCOMMAND_H_

#include "Command.h"
#include "Glyph.h"
#include "ActivityDiagram.h"

class AddGlyphCommand :
	public Command
{
private:
	ActivityDiagram *_activityDiagram;
	GlyphProperty _glyphProperty;
	bool _hasBeenExecuted;
public:
	AddGlyphCommand(ActivityDiagram *activityDiagram, int id, GLYPH_TYPE type, string text);
	~AddGlyphCommand(void);

	void execute();
	void unexecute();
};

#endif