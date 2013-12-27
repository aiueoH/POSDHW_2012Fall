#include "gtest\gtest.h"
#include "Activity.h"
#include "Edge.h"

class ActivityTest :
	public testing::Test
{
protected:
	Activity *_activity0, *_activity1;
	Edge *_edge0, *_edge1;

	virtual void SetUp()
	{
		_activity0 = new Activity(0, "A0");
		_activity1 = new Activity(1, "A1");
		_edge0 = new Edge(2, "E0");
		_edge1 = new Edge(3, "E1");
	}

	virtual void TearDown()
	{
		delete _activity0;
		delete _activity1;
		delete _edge0;
		delete _edge1;
	}
};

TEST_F(ActivityTest, canAddSource)
{
	EXPECT_FALSE(_activity0->canAddSource(_activity1));		// Activity 不能跟 Activity 連
	EXPECT_TRUE(_activity0->canAddSource(_edge0));
}

TEST_F(ActivityTest, canAddTarget)
{
	EXPECT_FALSE(_activity0->canAddTarget(_activity1));
	EXPECT_TRUE(_activity0->canAddTarget(_edge0));
	EXPECT_TRUE(_activity0->connectTo(_edge0));
	EXPECT_FALSE(_activity0->canAddTarget(_edge1));			// Activity 只能有一個 Target
}