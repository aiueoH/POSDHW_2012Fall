#ifndef ADDGLYPHSTATE_H_
#define ADDGLYPHSTATE_H_

#include "PresentationModelState.h"
#include "PresentationModel.h"
#include "Glyph.h"
#include "Globle.h"

class AddGlyphState :
	public PresentationModelState
{
private:
	GLYPH_TYPE _type;
public:
	AddGlyphState(PresentationModel *presentationModel);
	~AddGlyphState(void);

	void mousePressEvent(InputInformation inputInformation);
	void mouseMoveEvent(InputInformation inputInformation);
	void mouseReleaseEvent(InputInformation inputInformation);
};

#endif