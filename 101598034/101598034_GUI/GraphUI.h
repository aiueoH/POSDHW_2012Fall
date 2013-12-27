#ifndef GRAPHUI_H
#define GRAPHUI_H

#include "ui_GraphUI.h"
#include "PresentationModel.h"
#include "Glyph.h"
#include "ActivityDiagramPanel.h"
#include "ActivityDiagramTable.h"
#include "Observer.h"

#include <string>
#include <QLabel>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QBoxLayout>
#include <QTableWidget>
#include <QtGui/QMainWindow>

using namespace std;

class GraphUI : 
	public QMainWindow, public Observer
{
	Q_OBJECT
private:
	Ui::GraphUIClass ui;

	ActivityDiagramPanel *_activityDiagramPanel;
	ActivityDiagramTable *_activityDiagramTable;
	PresentationModel *_presentationModel;
	QScrollArea *_scrollArea;
	QBoxLayout *_mainLayout, *_glyphTableLayout;
	QWidget *_centralWidget;
	QLabel *_glyphLabel;

	// toolbar
	void setToolBar();
	void newToolBarQActions();
	void setToolBarIcons();
	void addToolBarActions();
	void setButtonsCheckable();
	void connectSignalAndSlot();
	QAction *_toolBarButtonOpenFile;
	QAction *_toolBarButtonSaveFile;
	QAction *_toolBarButtonIsExistPathBetween;
	QAction *_toolBarButtonClose;
	QAction *_toolBarButtonPoint;
	QAction *_toolBarButtonConnect;
	QAction *_toolBarButtonAddActivity;
	QAction *_toolBarButtonAddDecisionNode;
	QAction *_toolBarButtonAddInitialNode;
	QAction *_toolBarButtonAddFinalNode;
	QAction *_toolBarButtonAddEdge;
	QAction *_toolBarButtonUndo;
	QAction *_toolBarButtonRedo;
	QAction *_toolBarButtonDelete;
	QAction *_toolBarButtonCopy;
	QAction *_toolBarButtonCut;
	QAction *_toolBarButtonPaste;

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	void openFile();
	void saveFile();
	void isExistPathBetween();

	void update();

public:
	GraphUI(PresentationModel *presentationModel, QWidget *parent = 0, Qt::WFlags flags = 0);
	~GraphUI();

	public slots:
	void toolBarButtonOpenFile_clickListener();
	void toolBarButtonSaveFile_clickListener();
	void toolBarButtonIsExistPathBetween_clickListener();
	void toolBarButtonClose_clickListener();
	void toolBarButtonPoint_clickListener();
	void toolBarButtonConnect_clickListener();
	void toolBarButtonAddActivity_clickListener();
	void toolBarButtonAddDecisionNode_clickListener();
	void toolBarButtonAddInitialNode_clickListener();
	void toolBarButtonAddFinalNode_clickListener();
	void toolBarButtonAddEdge_clickListener();
	void toolBarButtonRedo_clickListener();
	void toolBarButtonUndo_clickListener();
	void toolBarButtonDelete_clickListener();
	void toolBarButtonCopy_clickListener();
	void toolBarButtonCut_clickListener();
	void toolBarButtonPaste_clickListener();
};

#endif // GRAPHUI_H