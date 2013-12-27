#include "PointState.h"

PointState::PointState(PresentationModel *presentationModel) : PresentationModelState(presentationModel)
{
	_pressX = 0;
	_pressY = 0;
	_bePressedGlyphId = -1;
	_isMovedGlyph = false;
}

PointState::~PointState(void)
{

}

void PointState::mousePressEvent(InputInformation inputInformation)
{
	_bePressedGlyphId = _presentationModel->getGlyphIdByCoordinate(inputInformation.x, inputInformation.y);
	if (_bePressedGlyphId != -1) // ���I�� glyph
	{
		if (inputInformation.isKeyControlPress)
		{
			bool isSelected = _presentationModel->getIsSelected(_bePressedGlyphId);
			_presentationModel->setIsSelected(_bePressedGlyphId, !isSelected);
		}
		else
		{
			if (_presentationModel->getSelectedGlyphs().size() == 1)
				_presentationModel->setAllGlyphIsSelected(false);
			_presentationModel->setIsSelected(_bePressedGlyphId, true);
		}
	}
	else // �S�I�� glyph
	{
		_presentationModel->setAllGlyphIsSelected(false);
	}
	// �i�_�ϥ��ˬd path �\��
	_presentationModel->setIsToolBarButtonIsExistPathBetweenEnabled(canUseExistPathBetweenButton(_presentationModel->getSelectedGlyphs()));
	// �������U���y��
	_pressX = inputInformation.x;
	_pressY = inputInformation.y;
	// ������쪺 glyphs ���e���A
	_previusGlyphPropertys = _presentationModel->getGlyphPropertys(_presentationModel->getSelectedGlyphIds());
}
void PointState::mouseMoveEvent(InputInformation inputInformation)
{
	int deltaX = inputInformation.x - _pressX;
	int deltaY = inputInformation.y - _pressY;
	// ����glyph
	if (_bePressedGlyphId != -1 && !inputInformation.isKeyControlPress)
	{
		vector<int> glyphIds = _presentationModel->getSelectedGlyphIds();
		for (unsigned int i = 0; i < glyphIds.size(); i++)
		{
			_isMovedGlyph = true;
			int id = glyphIds[i];
			GlyphProperty glyphProperty = _presentationModel->getGlyphProperty(id);
			// ��� Edge ��, �S������s�������p�~�i����
			if (_presentationModel->getGlyphType(id) == EDGE)
			{
				// �S������s�� �i����
				if (_presentationModel->getGlyphTargetIds(id).size() == 0 && _presentationModel->getGlyphSourceIds(id).size() == 0)
				{
					_presentationModel->setGlyphWidth(id, glyphProperty.width + deltaX);
					_presentationModel->setGlyphHeight(id, glyphProperty.height + deltaY);
				} 
				// ������s���� �L�k����
				else
				{
					continue;
				}
			}
			// ���� glyph
			_presentationModel->setGlyphX(id, glyphProperty.x + deltaX);
			_presentationModel->setGlyphY(id, glyphProperty.y + deltaY);
		}
	}
	_pressX = inputInformation.x;
	_pressY = inputInformation.y;
}
void PointState::mouseReleaseEvent(InputInformation inputInformation)
{
	// moveGlyphCommand
	if (_isMovedGlyph)
	{
		vector<int> ids = _presentationModel->getSelectedGlyphIds();
		vector<pair<GlyphProperty, GlyphProperty>> propertys;
		for (unsigned int i = 0; i < ids.size(); i++)
		{
			propertys.push_back(pair<GlyphProperty, GlyphProperty>(_previusGlyphPropertys[i], _presentationModel->getGlyphProperty(ids[i])));
		}
		_presentationModel->moveGlyphCommand(ids, propertys);
	}
	// clear
	_bePressedGlyphId = -1;
	_isMovedGlyph = false;
}

bool PointState::canUseExistPathBetweenButton(vector<Glyph*> glyphs)
{
	return glyphs.size() == 2 ? true : false;
}