#include "gtest\gtest.h"
#include "FinalNode.h"

class FinalNodeTest :
	public testing::Test
{
protected:
	FinalNode *_finalNode0, *_finalNode1;

	virtual void SetUp()
	{
		_finalNode0 = new FinalNode(0, "F0");
		_finalNode1 = new FinalNode(1, "F1");
	}

	virtual void TearDown()
	{
		delete _finalNode0;
		delete _finalNode1;
	}
};

TEST_F(FinalNodeTest, canAddTarget)
{
	EXPECT_FALSE(_finalNode0->canAddTarget(_finalNode1));
}