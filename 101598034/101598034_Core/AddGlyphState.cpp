#include "AddGlyphState.h"

AddGlyphState::AddGlyphState(PresentationModel *presentationModel) : PresentationModelState(presentationModel)
{
}

AddGlyphState::~AddGlyphState(void)
{
}

void AddGlyphState::mousePressEvent(InputInformation inputInformation)
{
	GlyphProperty property;
	property.type = inputInformation.addGlyphType;
	property.text = inputInformation.text;
	property.x = inputInformation.x;
	property.y = inputInformation.y;

	int width = property.text.length() * TEXT_LENGTH_PER_CHAR;
	if (width < GRAPH_WIDTH)
		width = GRAPH_WIDTH;
	if (inputInformation.addGlyphType == EDGE)
	{
		property.width = inputInformation.x + width;
		property.height = inputInformation.y;
	}
	else
	{
		property.width = width;
		property.height = GRAPH_HEIGHT;
	}
	_presentationModel->addGlyphCommand(property);
	_presentationModel->setPointState();
}

void AddGlyphState::mouseMoveEvent(InputInformation inputInformation)
{

}

void AddGlyphState::mouseReleaseEvent(InputInformation inputInformation)
{

}