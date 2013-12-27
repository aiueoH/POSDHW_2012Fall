#ifndef DELETEGLYPHCOMMAND_H_
#define DELETEGLYPHCOMMAND_H_

#include "Glyph.h"
#include "Command.h"
#include "ActivityDiagram.h"
#include "Tool.h"

#include <string>

class DeleteGlyphCommand :
	public Command
{
private:
	ActivityDiagram *_activityDiagram;
	vector<int> _ids, _glyphIndexs;
	vector<GlyphProperty> _propertys;

public:
	DeleteGlyphCommand(ActivityDiagram *activityDirgram, vector<int> id, vector<int> glyphIndex);
	~DeleteGlyphCommand(void);

	void execute();
	void unexecute();
};

#endif