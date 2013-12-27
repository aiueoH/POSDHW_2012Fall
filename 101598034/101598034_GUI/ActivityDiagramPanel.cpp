#include "ActivityDiagramPanel.h"


ActivityDiagramPanel::ActivityDiagramPanel(PresentationModel *presentationModel)
{
	_presentationModel = presentationModel;

	_isMouseClicked = false;
	setFixedSize(PANEL_WIDTH, PANEL_HEIGHT);
	initialDecodeDrawInstructionMap(&_decodeDrawInstruction);
	installEventFilter(this);
}


ActivityDiagramPanel::~ActivityDiagramPanel(void)
{
}

void ActivityDiagramPanel::paintEvent(QPaintEvent *event)
{
	_qPainter.begin(this);
	_qPainter.fillRect(0, 0, PANEL_WIDTH, PANEL_HEIGHT, Qt::white);

	// 先畫 component
	for (unsigned int i = 0; i < _glyphIds.size(); i++)
	{
		GLYPH_TYPE type = _presentationModel->getGlyphType(_glyphIds[i]);
		if (type != EDGE)
			drawByInstructions(_presentationModel->getDrawInstructions(_glyphIds[i]));
	}
	// 後畫 edge
	for (unsigned int i = 0; i < _glyphIds.size(); i++)
	{
		GLYPH_TYPE type = _presentationModel->getGlyphType(_glyphIds[i]);
		if (type == EDGE)
			drawByInstructions(_presentationModel->getDrawInstructions(_glyphIds[i]));
	}

	_qPainter.end();
}

void ActivityDiagramPanel::drawByInstructions(vector<DrawInstruction> drawInstructions)
{
	for (unsigned int i = 0; i < drawInstructions.size(); i++)
	{
		DRAW_INSTRUCTION_TYPE type = drawInstructions[i].type;
		DrawInstruction drawInstruction = drawInstructions[i];
		(this->*(_decodeDrawInstruction[type]))(&_qPainter, drawInstruction);
	}
}

bool ActivityDiagramPanel::eventFilter(QObject *object, QEvent *event)
{
	if (event->type() == QEvent::MouseMove)
	{
		QMouseEvent *e = (QMouseEvent*)event;
		_presentationModel->mouseEvent(e->x(), e->y(), PresentationModel::MOVE);
	}
	else if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *e = (QMouseEvent*)event;
		_presentationModel->mouseEvent(e->x(), e->y(), PresentationModel::LEFT_BUTTON_PRESS);
	}
	else if (event->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent *e = (QMouseEvent*)event;
		_presentationModel->mouseEvent(e->x(), e->y(), PresentationModel::LEFT_BUTTON_RELEASE);
	}

	return false;
}

void ActivityDiagramPanel::setGlyphIds(vector<int> glyphIds)
{
	_glyphIds = glyphIds;
}

void ActivityDiagramPanel::drawLine(QPainter *qPainter, DrawInstruction drawInstruction)
{
	int fromtX = drawInstruction.parameters[0].data;
	int fromtY = drawInstruction.parameters[1].data;
	int toX = drawInstruction.parameters[2].data;
	int toY = drawInstruction.parameters[3].data;
	qPainter->drawLine(fromtX, fromtY, toX, toY);
}

void ActivityDiagramPanel::drawEllipse(QPainter *qPainter, DrawInstruction drawInstruction)
{
	int x = drawInstruction.parameters[0].data;
	int y = drawInstruction.parameters[1].data;
	int width = drawInstruction.parameters[2].data;
	int height = drawInstruction.parameters[3].data;
	qPainter->drawEllipse(x, y, width, height);
}

void ActivityDiagramPanel::drawRoundedRect(QPainter *qPainter, DrawInstruction drawInstruction)
{
	int x = drawInstruction.parameters[0].data;
	int y = drawInstruction.parameters[1].data;
	int width = drawInstruction.parameters[2].data;
	int height = drawInstruction.parameters[3].data;
	int xRound = drawInstruction.parameters[4].data;
	int yRound = drawInstruction.parameters[5].data;
	qPainter->drawRoundedRect(x, y, width, height, xRound, yRound);
}

void ActivityDiagramPanel::drawText(QPainter *qPainter, DrawInstruction drawInstruction)
{
	int x = drawInstruction.parameters[0].data;
	int y = drawInstruction.parameters[1].data;
	int width = drawInstruction.parameters[2].data;
	int height = drawInstruction.parameters[3].data;
	string text = drawInstruction.parameters[4].text;
	qPainter->drawText(x, y, width, height, Qt::TextWordWrap, text.c_str());
}

void ActivityDiagramPanel::setColor(QPainter *qPainter, DrawInstruction drawInstruction)
{
	qPainter->setPen(QColor((Qt::GlobalColor)drawInstruction.parameters[0].data));
}

void ActivityDiagramPanel::setBrush(QPainter *qPainter, DrawInstruction drawInstruction)
{
	qPainter->setBrush((Qt::GlobalColor)drawInstruction.parameters[0].data);
}

void ActivityDiagramPanel::initialDecodeDrawInstructionMap(map<DRAW_INSTRUCTION_TYPE, DECODE_DRAW_INSTRUCTION> *typeMappingFunction)
{
	typeMappingFunction->insert(pair<DRAW_INSTRUCTION_TYPE, DECODE_DRAW_INSTRUCTION>(SET_PEN_COLOR, &ActivityDiagramPanel::setColor));
	typeMappingFunction->insert(pair<DRAW_INSTRUCTION_TYPE, DECODE_DRAW_INSTRUCTION>(SET_BRUSH, &ActivityDiagramPanel::setBrush));
	typeMappingFunction->insert(pair<DRAW_INSTRUCTION_TYPE, DECODE_DRAW_INSTRUCTION>(DRAW_LINE, &ActivityDiagramPanel::drawLine));
	typeMappingFunction->insert(pair<DRAW_INSTRUCTION_TYPE, DECODE_DRAW_INSTRUCTION>(DRAW_ELLIPSE, &ActivityDiagramPanel::drawEllipse));
	typeMappingFunction->insert(pair<DRAW_INSTRUCTION_TYPE, DECODE_DRAW_INSTRUCTION>(DRAW_ROUNDEDRECT, &ActivityDiagramPanel::drawRoundedRect));
	typeMappingFunction->insert(pair<DRAW_INSTRUCTION_TYPE, DECODE_DRAW_INSTRUCTION>(DRAW_TEXT, &ActivityDiagramPanel::drawText));
}