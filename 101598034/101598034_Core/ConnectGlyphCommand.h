#ifndef CONNECTGLYPHCOMMAND_H_
#define CONNECTGLYPHCOMMAND_H_

#include "Command.h"
#include "ActivityDiagram.h"

class ConnectGlyphCommand :
	public Command
{
private:
	ActivityDiagram *_activityDiagram;
	int _fromId, _toId;
public:
	ConnectGlyphCommand(ActivityDiagram *activityDiagram, int fromId, int toId);
	~ConnectGlyphCommand(void);

	void execute();
	void unexecute();
};

#endif
