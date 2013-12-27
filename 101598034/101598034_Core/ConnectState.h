#ifndef CONNECTSTATE_H_
#define CONNECTSTATE_H_

#include "PresentationModelState.h"
#include "PresentationModel.h"
#include "Glyph.h"

class ConnectState :
	public PresentationModelState
{
private:
	enum POINT_TYPE {TARGET, SOURCE};
	int _bePressEdgeId;
	POINT_TYPE _type;

public:
	ConnectState(PresentationModel *presentationModel);
	~ConnectState(void);

	void mousePressEvent(InputInformation inputInformation);
	void mouseMoveEvent(InputInformation inputInformation);
	void mouseReleaseEvent(InputInformation inputInformation);
};

#endif