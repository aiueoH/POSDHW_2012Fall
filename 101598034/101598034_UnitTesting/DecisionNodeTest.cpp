#include "gtest\gtest.h"
#include "DecisionNode.h"
#include "Edge.h"

class DecisionNodeTest :
	public testing::Test
{
protected:
	DecisionNode *_decisionNode0, *_decisionNode1;
	Edge *_edge0, *_edge1;

	virtual void SetUp()
	{
		_decisionNode0 = new DecisionNode(0, "D0");
		_decisionNode1 = new DecisionNode(1, "D1");
		_edge0 = new Edge(2, "E0");
		_edge1 = new Edge(3, "E1");
	}

	virtual void TearDown()
	{
		delete _decisionNode0;
		delete _decisionNode1;
		delete _edge0;
		delete _edge1;
	}
};

TEST_F(DecisionNodeTest, canAddSource)
{
	EXPECT_FALSE(_decisionNode0->canAddSource(_decisionNode1));		// DecisionNode 不能跟 DecisionNode 連
	EXPECT_TRUE(_decisionNode0->canAddSource(_edge0));
}

TEST_F(DecisionNodeTest, canAddTarget)
{
	EXPECT_FALSE(_decisionNode0->canAddTarget(_decisionNode1));
	EXPECT_TRUE(_decisionNode0->canAddTarget(_edge0));
	EXPECT_TRUE(_decisionNode0->connectTo(_edge0));
	EXPECT_FALSE(_decisionNode0->canAddTarget(_edge0));				// 不能連到重複的 Glyph
}