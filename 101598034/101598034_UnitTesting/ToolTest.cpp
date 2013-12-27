#include "gtest\gtest.h"
#include "Tool.h"
#include <string>
#include <vector>

class ToolTest :
	public testing::Test
{
protected:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(ToolTest, trim)
{
	EXPECT_EQ(Tool::trim(""), "");
	EXPECT_EQ(Tool::trim("ABC"), "ABC");
	EXPECT_EQ(Tool::trim(" ABC "), "ABC");
	EXPECT_EQ(Tool::trim(" A B C "), "A B C");
	EXPECT_EQ(Tool::trim("ABC "), "ABC");
	EXPECT_EQ(Tool::trim("A B C "), "A B C");
	EXPECT_EQ(Tool::trim(" ABC"), "ABC");
	EXPECT_EQ(Tool::trim(" A B C"), "A B C");
	EXPECT_EQ(Tool::trim("   A B C   "), "A B C");
}

TEST_F(ToolTest, splitStringToVector)
{
	vector<string> v;
	v = Tool::splitStringToVector("A", ",");
	EXPECT_EQ(v.size(), 1);
	EXPECT_EQ(v[0], "A");
	v = Tool::splitStringToVector("  A  ,  AAA   AAA  ,   A A A   ", ",");
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], "A");
	EXPECT_EQ(v[1], "AAA   AAA");
	EXPECT_EQ(v[2], "A A A");
}

TEST_F(ToolTest, charToString)
{
	EXPECT_EQ("C", Tool::charToString('C'));
}

TEST_F(ToolTest, stringToChar)
{
	EXPECT_EQ('C', Tool::stringToChar("C"));
	EXPECT_EQ('C', Tool::stringToChar("CCC"));
}