#include "GraphUI.h"
#include "ActivityDiagram.h"
#include "PresentationModel.h"
#include "Observer.h"

#include <QtGui/QApplication>
// �ˬd memory leak ��
#include <crtdbg.h>

int main(int argc, char *argv[])
{
	// �ˬd memory leak
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	ActivityDiagram activityDiagram;
	PresentationModel presentationModel(&activityDiagram);

	QApplication qApplication(argc, argv);
	GraphUI graphUI(&presentationModel);
	activityDiagram.setObserver((Observer*)&presentationModel);
	presentationModel.setObserver((Observer*)&graphUI);
	graphUI.show();
	return qApplication.exec();
}
