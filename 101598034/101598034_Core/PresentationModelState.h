#ifndef PRESENTATIONMODELSTATE_H_
#define PRESENTATIONMODELSTATE_H_

class PresentationModel;
struct InputInformation;

class PresentationModelState
{
protected:
	PresentationModel *_presentationModel;

public:
	PresentationModelState(PresentationModel *presentationModel);
	virtual ~PresentationModelState(void);

	virtual void mousePressEvent(InputInformation inputInformation) = 0;
	virtual void mouseMoveEvent(InputInformation inputInformation) = 0;
	virtual void mouseReleaseEvent(InputInformation inputInformation) = 0;
};

#endif