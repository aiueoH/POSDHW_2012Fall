#ifndef MOVEGLYPHCOMMAND_H_
#define MOVEGLYPHCOMMAND_H_

#include "Command.h"
#include "Glyph.h"
#include "ActivityDiagram.h"

#include <map>

class MoveGlyphCommand :
	public Command
{
private:
	ActivityDiagram *_activityDiagram;
	vector<pair<GlyphProperty, GlyphProperty>> _propertys;
	vector<int> _ids;
public:
	MoveGlyphCommand(ActivityDiagram *activityDiagram, vector<int> ids, vector<pair<GlyphProperty, GlyphProperty>> propertys);
	~MoveGlyphCommand(void);

	void execute();
	void unexecute();
};

#endif