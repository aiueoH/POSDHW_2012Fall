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
	if (_bePressedGlyphId != -1) // 有點到 glyph
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
	else // 沒點到 glyph
	{
		_presentationModel->setAllGlyphIsSelected(false);
	}
	// 可否使用檢查 path 功能
	_presentationModel->setIsToolBarButtonIsExistPathBetweenEnabled(canUseExistPathBetweenButton(_presentationModel->getSelectedGlyphs()));
	// 紀錄按下的座標
	_pressX = inputInformation.x;
	_pressY = inputInformation.y;
	// 紀錄選到的 glyphs 先前狀態
	_previusGlyphPropertys = _presentationModel->getGlyphPropertys(_presentationModel->getSelectedGlyphIds());
}
void PointState::mouseMoveEvent(InputInformation inputInformation)
{
	int deltaX = inputInformation.x - _pressX;
	int deltaY = inputInformation.y - _pressY;
	// 移動glyph
	if (_bePressedGlyphId != -1 && !inputInformation.isKeyControlPress)
	{
		vector<int> glyphIds = _presentationModel->getSelectedGlyphIds();
		for (unsigned int i = 0; i < glyphIds.size(); i++)
		{
			_isMovedGlyph = true;
			int id = glyphIds[i];
			GlyphProperty glyphProperty = _presentationModel->getGlyphProperty(id);
			// 選到 Edge 時, 沒有任何連結的情況才可移動
			if (_presentationModel->getGlyphType(id) == EDGE)
			{
				// 沒有任何連結 可移動
				if (_presentationModel->getGlyphTargetIds(id).size() == 0 && _presentationModel->getGlyphSourceIds(id).size() == 0)
				{
					_presentationModel->setGlyphWidth(id, glyphProperty.width + deltaX);
					_presentationModel->setGlyphHeight(id, glyphProperty.height + deltaY);
				} 
				// 有任何連結時 無法移動
				else
				{
					continue;
				}
			}
			// 移動 glyph
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