#include "gtest/gtest.h"

#include <stdio.h>
#include <vector>
// �ˬd memory leak ��
#include <crtdbg.h>

int main(int argc, char* argv[])
{
	// �ˬd memory leak
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");
}