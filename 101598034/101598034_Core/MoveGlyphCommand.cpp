#include "MoveGlyphCommand.h"

MoveGlyphCommand::MoveGlyphCommand(ActivityDiagram *activityDiagram, vector<int> ids, vector<pair<GlyphProperty, GlyphProperty>> propertys)
{
	_activityDiagram = activityDiagram;
	_ids = ids;
	_propertys = propertys;
}

MoveGlyphCommand::~MoveGlyphCommand(void)
{
}

void MoveGlyphCommand::execute()
{
	for (unsigned int i = 0; i < _ids.size(); i++)
	{
		if (_activityDiagram->getGlyphType(_ids[i]) == EDGE)
		{
			if (!_activityDiagram->getIsLonely(_ids[i]))
			{
				continue;
			}
		}
		_activityDiagram->setGlyphX(_ids[i], _propertys[i].second.x);
		_activityDiagram->setGlyphY(_ids[i], _propertys[i].second.y);
		_activityDiagram->setGlyphWidth(_ids[i], _propertys[i].second.width);
		_activityDiagram->setGlyphHeight(_ids[i], _propertys[i].second.height);
	}
}

void MoveGlyphCommand::unexecute()
{
	for (unsigned int i = _ids.size(); i > 0; i--)
	{
		unsigned int index = i - 1;
		if (_activityDiagram->getGlyphType(_ids[index]) == EDGE)
		{
			if (!_activityDiagram->getIsLonely(_ids[index]))
			{
				continue;
			}
		}
		_activityDiagram->setGlyphX(_ids[index], _propertys[index].first.x);
		_activityDiagram->setGlyphY(_ids[index], _propertys[index].first.y);
		_activityDiagram->setGlyphWidth(_ids[index], _propertys[index].first.width);
		_activityDiagram->setGlyphHeight(_ids[index], _propertys[index].first.height);
	}
}