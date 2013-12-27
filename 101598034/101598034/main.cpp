// 101598034.cpp : 定義主控台應用程式的進入點。
#include "stdafx.h"
#include "TextUi.h"
#include "ActivityDiagram.h"
#include "Tool.h"

#include <iostream>
#include <vector>
// 檢查 memory leak 用
#include <crtdbg.h>

int _tmain(int argc, _TCHAR* argv[])
{
	// 檢查 memory leak
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	
	{
		ActivityDiagram activityDiagram;
		TextUi textUi(&activityDiagram);
		textUi.startUi();
	}

	system("PAUSE");
	return 0;
}