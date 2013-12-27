#include "gtest\gtest.h"
#include "GlyphComponent.h"
#include "DecisionNode.h"
#include "Edge.h"

class GlyphComponentTest :
	public testing::Test
{
protected:
	GlyphComponent *_decisionNode0, *_decisionNode1;
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

TEST_F(GlyphComponentTest, connectTo)
{
	EXPECT_FALSE(_decisionNode0->connectTo(_decisionNode0)); // 不能連自己
	EXPECT_FALSE(_decisionNode0->connectTo(_decisionNode1)); // 不能連非 Edge
	EXPECT_TRUE(_decisionNode0->connectTo(_edge0));
	EXPECT_FALSE(_decisionNode0->connectTo(_edge0));	 // 不能連已經連過的
}

TEST_F(GlyphComponentTest, beConnectedFrom)
{
	EXPECT_FALSE(_decisionNode0->beConnectedFrom(_decisionNode0));	// 不能被自己連
	EXPECT_FALSE(_decisionNode0->beConnectedFrom(_decisionNode1));	// 不能被非 Edge 連
	EXPECT_TRUE(_decisionNode0->beConnectedFrom(_edge0));
	EXPECT_FALSE(_decisionNode0->beConnectedFrom(_edge0));		// 不能被已經連過的連
	EXPECT_TRUE(_decisionNode0->beConnectedFrom(_edge1));
}

TEST_F(GlyphComponentTest, isConnected)
{
	// 被連
	EXPECT_FALSE(_decisionNode0->isConnected(_edge0));
	EXPECT_TRUE(_decisionNode0->beConnectedFrom(_edge0));
	EXPECT_TRUE(_decisionNode0->isConnected(_edge0));
	// 連
	EXPECT_FALSE(_decisionNode0->isConnected(_edge1));
	EXPECT_TRUE(_decisionNode0->connectTo(_edge1));
	EXPECT_TRUE(_decisionNode0->isConnected(_edge1));
}

TEST_F(GlyphComponentTest, isSourcesEmpty)
{
	EXPECT_TRUE(_decisionNode0->isSourcesEmpty());
	EXPECT_TRUE(_decisionNode0->beConnectedFrom(_edge0));
	EXPECT_FALSE(_decisionNode0->isSourcesEmpty());
}

TEST_F(GlyphComponentTest, isTargetsEmpty)
{
	EXPECT_TRUE(_decisionNode0->isTargetsEmpty());
	EXPECT_TRUE(_decisionNode0->connectTo(_edge0));
	EXPECT_FALSE(_decisionNode0->isTargetsEmpty());
}

TEST_F(GlyphComponentTest, removeSource)
{
	EXPECT_FALSE(_decisionNode0->removeSource(_edge0));
	EXPECT_TRUE(_decisionNode0->beConnectedFrom(_edge0));
	EXPECT_FALSE(_decisionNode0->removeSource(_edge1));
	EXPECT_TRUE(_decisionNode0->removeSource(_edge0));
	EXPECT_FALSE(_decisionNode0->removeSource(_edge0));
}

TEST_F(GlyphComponentTest, removeTarget)
{
	EXPECT_FALSE(_decisionNode0->removeTarget(_edge0));
	EXPECT_TRUE(_decisionNode0->connectTo(_edge0));
	EXPECT_FALSE(_decisionNode0->removeTarget(_edge1));
	EXPECT_TRUE(_decisionNode0->removeTarget(_edge0));
	EXPECT_FALSE(_decisionNode0->removeTarget(_edge0));
}