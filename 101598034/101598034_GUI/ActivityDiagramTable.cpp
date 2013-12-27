#include "ActivityDiagramTable.h"

ActivityDiagramTable::ActivityDiagramTable(PresentationModel *presentationModel)
{
	_presentationModel = presentationModel;
	_isUpdating = false;

	// ³]©w column header
	setColumnCount(TABLE_HEADER_COUNT);
	QStringList horizontalHeaders;
	horizontalHeaders << tr(TABLE_HEADER_NAME_TYPE.c_str());
	horizontalHeaders << tr(TABLE_HEADER_NAME_TEXT.c_str());
	setHorizontalHeaderLabels(horizontalHeaders);
	horizontalHeader()->setResizeMode(QHeaderView::Stretch);

	update();

	connect(this, SIGNAL(cellChanged(int, int)), this, SLOT(itemChangeListener(int, int)));
}

ActivityDiagramTable::~ActivityDiagramTable(void)
{
	deleteTextItemsMemory();
	deleteTypeItemsMemory();
}

void ActivityDiagramTable::update()
{
	_isUpdating = true;
	updateTableItems();
	show();
	_isUpdating = false;
}

void ActivityDiagramTable::updateTableItems()
{
	_idHeaders.clear();
	deleteTextItemsMemory();
	deleteTypeItemsMemory();
	
	vector<int> glyphIds = _presentationModel->getGlyphIds();
	for (int i = 0; i < glyphIds.size(); i++)
	{
		GlyphProperty glyphProperty = _presentationModel->getGlyphProperty(glyphIds[i]);
		// vertical header
		_idHeaders << Tool::intToString(glyphProperty.id).c_str();
		// new table item
		QTableWidgetItem *type = new QTableWidgetItem(glyphProperty.typeName.c_str());
		QTableWidgetItem *text = new QTableWidgetItem(glyphProperty.text.c_str());
		type->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
		text->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
		if (glyphProperty.type == EDGE || glyphProperty.type == ACTIVITY)
			text->setFlags(text->flags() | Qt::ItemIsEditable);
		// set into table
		setItem(i, TABLE_HEADER_INDEX_TYPE, type);
		setItem(i, TABLE_HEADER_INDEX_TEXT, text);
		// push into vector to record pointer
		_typeItems.push_back(type);
		_textItems.push_back(text);
	}
	setVerticalHeaderLabels(_idHeaders);
	setRowCount(glyphIds.size());
}

void ActivityDiagramTable::deleteTextItemsMemory()
{
	while (!_textItems.empty())
	{
		delete _textItems.back();
		_textItems.pop_back();
	}
}

void ActivityDiagramTable::deleteTypeItemsMemory()
{
	while (!_typeItems.empty())
	{
		delete _typeItems.back();
		_typeItems.pop_back();
	}
}

void ActivityDiagramTable::itemChangeListener(int row, int column)
{
	if (!_isUpdating && column == TABLE_HEADER_INDEX_TEXT)
	{
		int id = atoi(_idHeaders[row].toStdString().c_str());
		string text = item(row, column)->text().toStdString();
		_presentationModel->editTextCommand(id, text);
	}
}