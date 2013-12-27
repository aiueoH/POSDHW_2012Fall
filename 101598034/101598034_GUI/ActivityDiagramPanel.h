#ifndef ACTIVITYDIAGRAMPANEL_H_
#define ACTIVITYDIAGRAMPANEL_H_

#include "PresentationModel.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <vector>
#include <string>

using namespace std;

class ActivityDiagramPanel :
	public QWidget
{
private:
	PresentationModel *_presentationModel;
	QPainter _qPainter;
	vector<int> _glyphIds;

	int _mouseClickedX, _mouseClickedY;
	bool _isMouseClicked;

	void drawByInstructions(vector<DrawInstruction> drawInstructions);
	void drawLine(QPainter *qPainter, DrawInstruction drawInstruction);
	void drawEllipse(QPainter *qPainter, DrawInstruction drawInstruction);
	void drawRoundedRect(QPainter *qPainter, DrawInstruction drawInstruction);
	void drawText(QPainter *qPainter, DrawInstruction drawInstruction);
	void setColor(QPainter *qPainter, DrawInstruction drawInstruction);
	void setBrush(QPainter *qPainter, DrawInstruction drawInstruction);

	// 各種 type 對應的 function
	typedef void (ActivityDiagramPanel::*DECODE_DRAW_INSTRUCTION)(QPainter*, DrawInstruction);
	map<DRAW_INSTRUCTION_TYPE, DECODE_DRAW_INSTRUCTION> _decodeDrawInstruction;
	void initialDecodeDrawInstructionMap(map<DRAW_INSTRUCTION_TYPE, DECODE_DRAW_INSTRUCTION> *map);


public:
	ActivityDiagramPanel(PresentationModel *presentationModel);
	~ActivityDiagramPanel(void);

	void setGlyphIds(vector<int> glyphIds);

protected:
	bool eventFilter(QObject *object, QEvent *event);
	void paintEvent(QPaintEvent *event);
};

#endif