#ifndef GRAPHUI_H
#define GRAPHUI_H

#include "ui_GraphUI.h"
#include "PresentationModel.h"
#include "Glyph.h"
#include "ActivityDiagramPanel.h"
#include "ActivityDiagramTable.h"
#include "Observer.h"

#include <string>
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
	QScrollArea *_qScrollArea;
	QBoxLayout *_qBoxLayout;
	QWidget *_centralWidget;

	// toolbar
	void setToolBar();
	void newToolBarQActions();
	void setToolBarIcons();
	void addToolBarActions();
	void setButtonsCheckable();
	void connectSignalAndSlot();
	QAction *_toolBarButtonOpenFile;
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

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	bool eventFilter(QObject *object, QEvent *event);

	void openFile();
	void isExistPathBetween();

	void update();

public:
	GraphUI(PresentationModel *presentationModel, QWidget *parent = 0, Qt::WFlags flags = 0);
	~GraphUI();

public slots:
	void toolBarButtonOpenFile_clickListener();
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
};

#endif // GRAPHUI_H