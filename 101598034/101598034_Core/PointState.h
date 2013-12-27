#ifndef POINTSTATE_H_
#define POINTSTATE_H_

#include "PresentationModelState.h"
#include "PresentationModel.h"
#include "Glyph.h"

class PointState :
	public PresentationModelState
{
private:
	int _pressX, _pressY;
	int _bePressedGlyphId;
	vector<GlyphProperty> _previusGlyphPropertys;
	bool _isMovedGlyph;
	
	bool canUseExistPathBetweenButton(vector<Glyph*> glyphs);

public:
	PointState(PresentationModel *presentationModel);
	~PointState(void);

	void mousePressEvent(InputInformation inputInformation);
	void mouseMoveEvent(InputInformation inputInformation);
	void mouseReleaseEvent(InputInformation inputInformation);
};

#endif