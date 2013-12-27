#include "gtest/gtest.h"

#include <stdio.h>
#include <vector>
// ¿À¨d memory leak •Œ
#include <crtdbg.h>

int main(int argc, char* argv[])
{
	// ¿À¨d memory leak
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");
}