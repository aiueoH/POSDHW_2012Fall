#ifndef EDITTEXTCOMMAND_H_
#define EDITTEXTCOMMAND_H_

#include "Command.h"
#include "Glyph.h"
#include "ActivityDiagram.h"

class EditTextCommand :
	public Command
{
private:
	ActivityDiagram *_activityDiagram;
	int _id;
	string _text, _originalText;
public:
	EditTextCommand(ActivityDiagram *activityDiagram, int id, string text);
	~EditTextCommand(void);

	void execute();
	void unexecute();
};

#endif