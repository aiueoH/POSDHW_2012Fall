#include "ConnectState.h"

ConnectState::ConnectState(PresentationModel *presentationModel) : PresentationModelState(presentationModel)
{
	_bePressEdgeId = -1;
}

ConnectState::~ConnectState(void)
{
}

void ConnectState::mousePressEvent(InputInformation inputInformation)
{
	int edgeId;
	// target connection point
	edgeId = _presentationModel->getGlyphByCoordinateOnTargetConnectionPoint(inputInformation.x, inputInformation.y);
	if (edgeId != -1)
	{
		_type = TARGET;
		_bePressEdgeId = edgeId;
		vector<int> targetIds = _presentationModel->getGlyphTargetIds(edgeId);
		if (targetIds.size() != 0)
			_presentationModel->deleteConnection(edgeId, targetIds[0]);
	}
	// source connection point
	edgeId = _presentationModel->getGlyphByCoordinateOnSourceConnectionPoint(inputInformation.x, inputInformation.y);
	if (edgeId != -1)
	{
		_type = SOURCE;
		_bePressEdgeId = edgeId;
		vector<int> sourceIds = _presentationModel->getGlyphSourceIds(edgeId);
		if (sourceIds.size() != 0)
			_presentationModel->deleteConnection(sourceIds[0], edgeId);
	}
}

void ConnectState::mouseMoveEvent(InputInformation inputInformation)
{
	if (_bePressEdgeId != -1)
		if (_type == TARGET)
		{
			_presentationModel->setGlyphWidth(_bePressEdgeId, inputInformation.x - EDGE_CONNECTION_POINT_WIDTH / 2);
			_presentationModel->setGlyphHeight(_bePressEdgeId, inputInformation.y);
		}
		else if (_type == SOURCE)
		{
			_presentationModel->setGlyphX(_bePressEdgeId, inputInformation.x + EDGE_CONNECTION_POINT_WIDTH / 2);
			_presentationModel->setGlyphY(_bePressEdgeId, inputInformation.y);
		}
}

void ConnectState::mouseReleaseEvent(InputInformation inputInformation)
{
	if (_bePressEdgeId != -1)
	{
		int componentId = _presentationModel->getGlyphIdByCoordinate(inputInformation.x, inputInformation.y);
		if (componentId != -1)
			if (_type == TARGET)
				_presentationModel->connectGlyphCommand(_bePressEdgeId, componentId);
			else if (_type == SOURCE)
				_presentationModel->connectGlyphCommand(componentId, _bePressEdgeId);
	}
	_bePressEdgeId = -1;
}