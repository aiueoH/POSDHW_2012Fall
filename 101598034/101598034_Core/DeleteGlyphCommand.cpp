#include "DeleteGlyphCommand.h"

DeleteGlyphCommand::DeleteGlyphCommand(ActivityDiagram *activityDirgram, vector<int> ids, vector<int> glyphIndexs)
{
	_activityDiagram = activityDirgram;
	_ids = ids;
	_glyphIndexs = glyphIndexs;
	_propertys = _activityDiagram->getGlyphPropertys(ids);
}

DeleteGlyphCommand::~DeleteGlyphCommand(void)
{
}

void DeleteGlyphCommand::execute()
{
	for (unsigned int i = 0; i < _ids.size(); i++)
	{
		_activityDiagram->deleteGlyph(_ids[i]);
	}
}

void DeleteGlyphCommand::unexecute()
{
	for (unsigned int i = _ids.size(); i > 0; i--)
	{
		unsigned int index = i - 1;
		// 建立 glyph
		_activityDiagram->addGlyph(_ids[index], _propertys[index].type, _propertys[index].text, _glyphIndexs[index]);
		_activityDiagram->setGlyphProperty(_ids[index], _propertys[index]);
		// 建立連線
		vector<int> targets = _propertys[index].targetIds;
		vector<int> sources = _propertys[index].sourceIds;
		for (unsigned int j = 0; j < targets.size(); j++)
			_activityDiagram->connectGlyph(_ids[index], targets[j]);
		for (unsigned int j = 0; j < sources.size(); j++)
			_activityDiagram->connectGlyph(sources[j], _ids[index]);
	}
}
