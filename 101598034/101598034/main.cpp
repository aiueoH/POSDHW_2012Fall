// 101598034.cpp : �w�q�D���x���ε{�����i�J�I�C
#include "stdafx.h"
#include "TextUi.h"
#include "ActivityDiagram.h"
#include "Tool.h"

#include <iostream>
#include <vector>
// �ˬd memory leak ��
#include <crtdbg.h>

int _tmain(int argc, _TCHAR* argv[])
{
	// �ˬd memory leak
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	
	{
		ActivityDiagram activityDiagram;
		TextUi textUi(&activityDiagram);
		textUi.startUi();
	}

	system("PAUSE");
	return 0;
}