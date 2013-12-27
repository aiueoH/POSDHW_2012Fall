#include "gtest\gtest.h"
#include "DecisionNode.h"
#include "Edge.h"

class EdgeTest :
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

TEST_F(EdgeTest, connectTo)
{
	EXPECT_FALSE(_edge0->connectTo(_edge1));
	EXPECT_TRUE(_edge0->connectTo(_decisionNode0));
}

TEST_F(EdgeTest, beConnectedFrom)
{
	EXPECT_FALSE(_edge0->beConnectedFrom(_edge1));
	EXPECT_TRUE(_edge0->beConnectedFrom(_decisionNode0));
}

TEST_F(EdgeTest, canAddSource)
{
	EXPECT_FALSE(_edge0->canAddSource(_edge1));
	EXPECT_TRUE(_edge0->canAddSource(_decisionNode0));
	EXPECT_TRUE(_edge0->beConnectedFrom(_decisionNode0));
	EXPECT_FALSE(_edge0->canAddSource(_decisionNode1));
}

TEST_F(EdgeTest, canAddTarget)
{
	EXPECT_FALSE(_edge0->canAddTarget(_edge0));
	EXPECT_TRUE(_edge0->canAddTarget(_decisionNode0));
	EXPECT_TRUE(_edge0->connectTo(_decisionNode0));
	EXPECT_FALSE(_edge0->canAddTarget(_decisionNode1));
}

TEST_F(EdgeTest, removeSource)
{
	EXPECT_FALSE(_edge0->removeSource(_decisionNode0));
	EXPECT_TRUE(_edge0->beConnectedFrom(_decisionNode0));
	EXPECT_TRUE(_edge0->removeSource(_decisionNode0));
	EXPECT_FALSE(_edge0->removeSource(_decisionNode0));
}

TEST_F(EdgeTest, removeTarget)
{
	EXPECT_FALSE(_edge0->removeTarget(_decisionNode0));
	EXPECT_TRUE(_edge0->connectTo(_decisionNode0));
	EXPECT_TRUE(_edge0->removeTarget(_decisionNode0));
	EXPECT_FALSE(_edge0->removeTarget(_decisionNode0));
}