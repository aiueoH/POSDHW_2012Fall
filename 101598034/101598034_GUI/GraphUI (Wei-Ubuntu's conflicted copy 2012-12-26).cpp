#include "GraphUI.h"

GraphUI::GraphUI(PresentationModel *presentationModel, QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	_presentationModel = presentationModel;
	_activityDiagramPanel = new ActivityDiagramPanel(_presentationModel);
	_activityDiagramTable = new ActivityDiagramTable(_presentationModel);
	ui.setupUi(this);
	setToolBar();

	// mainWindow( centralWidget( layout( scrolArea, table ) ) )
	_qScrollArea = new QScrollArea();
	_qScrollArea->setWidget(_activityDiagramPanel);
	_qBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	_qBoxLayout->addWidget(_qScrollArea);
	_qBoxLayout->addWidget(_activityDiagramTable);
	_centralWidget = new QWidget();
	_centralWidget->setLayout(_qBoxLayout);
	setCentralWidget(_centralWidget);

	installEventFilter(this);
	update();
}

GraphUI::~GraphUI()
{
	delete _activityDiagramPanel;
}

void GraphUI::toolBarButtonOpenFile_clickListener()
{
	openFile();
}

void GraphUI::toolBarButtonIsExistPathBetween_clickListener()
{
	isExistPathBetween();
}

void GraphUI::toolBarButtonClose_clickListener()
{
	close();
}

void GraphUI::toolBarButtonPoint_clickListener()
{
	_presentationModel->setPointState();
}

void GraphUI::toolBarButtonConnect_clickListener()
{
	_presentationModel->setConnectState();
}

void GraphUI::toolBarButtonAddActivity_clickListener()
{
	bool isSubmit = false;
	char *title = "Enter text";
	char *labelText = "Please enter the text";
	QString text = QInputDialog::getText(this, tr(title), tr(labelText), QLineEdit::Normal, "", &isSubmit);
	if (isSubmit)
		_presentationModel->setAddGlyphState(Glyph::ACTIVITY, text.toStdString());
}

void GraphUI::toolBarButtonAddDecisionNode_clickListener()
{
	_presentationModel->setAddGlyphState(Glyph::DECISION_NODE, "");
}

void GraphUI::toolBarButtonAddInitialNode_clickListener()
{
	_presentationModel->setAddGlyphState(Glyph::INITIAL_NODE, "");
}

void GraphUI::toolBarButtonAddFinalNode_clickListener()
{
	_presentationModel->setAddGlyphState(Glyph::FINAL_NODE, "");
}

void GraphUI::toolBarButtonAddEdge_clickListener()
{	
	bool isSubmit = false;
	char *title = "Enter text";
	char *labelText = "Please enter the text";
	QString text = QInputDialog::getText(this, tr(title), tr(labelText), QLineEdit::Normal, "", &isSubmit);
	if (isSubmit)
		_presentationModel->setAddGlyphState(Glyph::EDGE, text.toStdString());
}

void GraphUI::toolBarButtonRedo_clickListener()
{
	_presentationModel->redo();
}

void GraphUI::toolBarButtonUndo_clickListener()
{
	_presentationModel->undo();
}

void GraphUI::openFile()
{
	string title = "Open Diagram";
	string dir = "C:/";
	string fileType = "Add Files (*.add);;All files (*.*)";

	// alert fileDialog and get file name
	QString filename = QFileDialog::getOpenFileName(this, tr(title.c_str()), dir.c_str(), tr(fileType.c_str()) );
	if( !filename.isNull() )
	{
		// load Activity Diagram
		_presentationModel->loadActivityDiagramFile((string)filename.toLocal8Bit());
		_presentationModel->computeGlyphsPosition();
		_presentationModel->setPointState();
	}
	update();
}

void GraphUI::isExistPathBetween()
{
	QMessageBox qMessageBox;
	qMessageBox.setWindowTitle("Check paths between two glyphs");
	if (_presentationModel->isExistPathBetween())
		qMessageBox.setText("There exists a path linking the two glyphs.");
	else
		qMessageBox.setText("There is no path linked the two glyphs.");
	qMessageBox.exec();
}

void GraphUI::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
		_presentationModel->isKeyControlPress(true);
}

void GraphUI::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
		_presentationModel->isKeyControlPress(false);
}

void GraphUI::update()
{
	// menu
	ui.actionCheck_paths_between_two_glyphs->setEnabled(_presentationModel->isToolBarButtonIsExistPathBetweenEnabled());
	// toolBar
	_toolBarButtonIsExistPathBetween->setEnabled(_presentationModel->isToolBarButtonIsExistPathBetweenEnabled());
	_toolBarButtonPoint->setChecked(_presentationModel->isToolBarButtonPointChecked());
	_toolBarButtonConnect->setChecked(_presentationModel->isToolBarButtonConnectChecked());
	_toolBarButtonAddActivity->setChecked(_presentationModel->isToolBarButtonAddActivityChecked());
	_toolBarButtonAddDecisionNode->setChecked(_presentationModel->isToolBarButtonAddDecisionNodeChecked());
	_toolBarButtonAddInitialNode->setChecked(_presentationModel->isToolBarButtonAddInitialNodeChecked());
	_toolBarButtonAddFinalNode->setChecked(_presentationModel->isToolBarButtonAddFinalNodeChecked());
	_toolBarButtonAddEdge->setChecked(_presentationModel->isToolBarButtonAddEdgeChecked());
	_toolBarButtonRedo->setEnabled(_presentationModel->isToolBarButtonRedoEnabled());
	_toolBarButtonUndo->setEnabled(_presentationModel->isToolBarButtonUndoEnabled());
	// panel
	_activityDiagramPanel->setGlyphIds(_presentationModel->getGlyphIds());
	_activityDiagramPanel->update();
	// table
	_activityDiagramTable->update();
}

void GraphUI::setToolBar()
{
	newToolBarQActions();
	setToolBarIcons();
	addToolBarActions();
	setButtonsCheckable();
	connectSignalAndSlot();
}

bool GraphUI::eventFilter(QObject *object, QEvent *event)
{
	//update();
	return false;
}

void GraphUI::newToolBarQActions()
{
	_toolBarButtonOpenFile = new QAction(ui.mainToolBar);
	_toolBarButtonIsExistPathBetween = new QAction(ui.mainToolBar);
	_toolBarButtonClose = new QAction(ui.mainToolBar);
	_toolBarButtonPoint = new QAction(ui.mainToolBar);
	_toolBarButtonConnect = new QAction(ui.mainToolBar);
	_toolBarButtonAddActivity = new QAction(ui.mainToolBar);
	_toolBarButtonAddDecisionNode = new QAction(ui.mainToolBar);
	_toolBarButtonAddInitialNode = new QAction(ui.mainToolBar);
	_toolBarButtonAddFinalNode = new QAction(ui.mainToolBar);
	_toolBarButtonAddEdge = new QAction(ui.mainToolBar);
	_toolBarButtonRedo = new QAction(ui.mainToolBar);
	_toolBarButtonUndo = new QAction(ui.mainToolBar);
}

void GraphUI::setToolBarIcons()
{
	_toolBarButtonOpenFile->setIcon(QIcon("./Resources/openfile.png"));
	_toolBarButtonIsExistPathBetween->setIcon(QIcon("./Resources/path.png"));
	_toolBarButtonClose->setIcon(QIcon("./Resources/close.png"));
	_toolBarButtonPoint->setIcon(QIcon("./Resources/cursor.png"));
	_toolBarButtonConnect->setIcon(QIcon("./Resources/connect.png"));
	_toolBarButtonAddActivity->setIcon(QIcon("./Resources/activity.png"));
	_toolBarButtonAddDecisionNode->setIcon(QIcon("./Resources/decisionNode.png"));
	_toolBarButtonAddInitialNode->setIcon(QIcon("./Resources/initialNode.png"));
	_toolBarButtonAddFinalNode->setIcon(QIcon("./Resources/finalNode.png"));
	_toolBarButtonAddEdge->setIcon(QIcon("./Resources/edge.png"));
	_toolBarButtonRedo->setIcon(QIcon("./Resources/redo.png"));
	_toolBarButtonUndo->setIcon(QIcon("./Resources/undo.png"));
}

void GraphUI::addToolBarActions()
{
	ui.mainToolBar->addAction(_toolBarButtonOpenFile);
	ui.mainToolBar->addAction(_toolBarButtonIsExistPathBetween);
	ui.mainToolBar->addAction(_toolBarButtonClose);
	ui.mainToolBar->addAction(_toolBarButtonUndo);
	ui.mainToolBar->addAction(_toolBarButtonRedo);
	ui.mainToolBar->addAction(_toolBarButtonPoint);
	ui.mainToolBar->addAction(_toolBarButtonAddInitialNode);
	ui.mainToolBar->addAction(_toolBarButtonAddActivity);
	ui.mainToolBar->addAction(_toolBarButtonAddDecisionNode);
	ui.mainToolBar->addAction(_toolBarButtonAddEdge);
	ui.mainToolBar->addAction(_toolBarButtonAddFinalNode);
	ui.mainToolBar->addAction(_toolBarButtonConnect);
}

void GraphUI::setButtonsCheckable()
{
	_toolBarButtonPoint->setCheckable(true);
	_toolBarButtonConnect->setCheckable(true);
	_toolBarButtonAddActivity->setCheckable(true);
	_toolBarButtonAddDecisionNode->setCheckable(true);
	_toolBarButtonAddInitialNode->setCheckable(true);
	_toolBarButtonAddFinalNode->setCheckable(true);
	_toolBarButtonAddEdge->setCheckable(true);
}

void GraphUI::connectSignalAndSlot()
{
	///////////////////////////////////////////////////////////////////////
	// toolBar
	///////////////////////////////////////////////////////////////////////
	// open, close, checkPath
	connect(_toolBarButtonOpenFile, SIGNAL(triggered()), this, SLOT(toolBarButtonOpenFile_clickListener()));
	connect(_toolBarButtonClose, SIGNAL(triggered()), this, SLOT(toolBarButtonClose_clickListener()));
	connect(_toolBarButtonIsExistPathBetween, SIGNAL(triggered()), this, SLOT(toolBarButtonIsExistPathBetween_clickListener()));
	// undo, redo
	connect(_toolBarButtonUndo, SIGNAL(triggered()), this, SLOT(toolBarButtonUndo_clickListener()));
	connect(_toolBarButtonRedo, SIGNAL(triggered()), this, SLOT(toolBarButtonRedo_clickListener()));
	// point, addGlyph, connect
	connect(_toolBarButtonConnect, SIGNAL(triggered()), this, SLOT(toolBarButtonConnect_clickListener()));
	connect(_toolBarButtonPoint, SIGNAL(triggered()), this, SLOT(toolBarButtonPoint_clickListener()));
	connect(_toolBarButtonAddActivity, SIGNAL(triggered()), this, SLOT(toolBarButtonAddActivity_clickListener()));
	connect(_toolBarButtonAddDecisionNode, SIGNAL(triggered()), this, SLOT(toolBarButtonAddDecisionNode_clickListener()));
	connect(_toolBarButtonAddInitialNode, SIGNAL(triggered()), this, SLOT(toolBarButtonAddInitialNode_clickListener()));
	connect(_toolBarButtonAddFinalNode, SIGNAL(triggered()), this, SLOT(toolBarButtonAddFinalNode_clickListener()));
	connect(_toolBarButtonAddEdge, SIGNAL(triggered()), this, SLOT(toolBarButtonAddEdge_clickListener()));
	///////////////////////////////////////////////////////////////////////
	// menuBar
	///////////////////////////////////////////////////////////////////////
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(toolBarButtonOpenFile_clickListener()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(toolBarButtonClose_clickListener()));
	connect(ui.actionCheck_paths_between_two_glyphs, SIGNAL(triggered()), this, SLOT(toolBarButtonIsExistPathBetween_clickListener()));
}