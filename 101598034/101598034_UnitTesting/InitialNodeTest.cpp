#include "gtest\gtest.h"
#include "GlyphComponent.h"
#include "InitialNode.h"
#include "Edge.h"

class InitialNodeTest :
	public testing::Test
{
protected:
	GlyphComponent *_initialNode0, *_initialNode1;
	Edge *_edge0, *_edge1;

	virtual void SetUp()
	{
		_initialNode0 = new InitialNode(0, "I0");
		_initialNode1 = new InitialNode(1, "I1");
		_edge0 = new Edge(2, "E0");
		_edge1 = new Edge(3, "E1");
	}

	virtual void TearDown()
	{
		delete _initialNode0;
		delete _initialNode1;
		delete _edge0;
		delete _edge1;
	}
};

TEST_F(InitialNodeTest, canAddSource)
{
	EXPECT_FALSE(_initialNode0->canAddSource(_initialNode1));
	EXPECT_FALSE(_initialNode0->canAddSource(_edge0));
}

TEST_F(InitialNodeTest, canAddTarget)
{
	EXPECT_FALSE(_initialNode0->canAddTarget(_initialNode1));
	EXPECT_TRUE(_initialNode0->canAddTarget(_edge0));
	EXPECT_TRUE(_initialNode0->connectTo(_edge0));
	EXPECT_FALSE(_initialNode0->canAddTarget(_edge1));			// 只能有一個 Target
}