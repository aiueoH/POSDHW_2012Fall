#ifndef ACTIVITYDIAGRAMTABLE_H_
#define ACTIVITYDIAGRAMTABLE_H_

#include "Globle.h"
#include "Tool.h"
#include "Glyph.h"
#include "PresentationModel.h"

#include <vector>
#include <string>
#include <QTableWidget>
#include <QHeaderView>

using namespace std;

class ActivityDiagramTable :
	public QTableWidget
{
	Q_OBJECT
private:
	PresentationModel *_presentationModel;
	QStringList _idHeaders;
	vector<QTableWidgetItem*> _typeItems;
	vector<QTableWidgetItem*> _textItems;
	bool _isUpdating;

	void showItems();
	void updateTableItems();

	void deleteTypeItemsMemory();
	void deleteTextItemsMemory();

private slots:
	void itemChangeListener(int, int);

public:
	ActivityDiagramTable(PresentationModel *presentationModel);
	~ActivityDiagramTable(void);

	void update();
};

#endif