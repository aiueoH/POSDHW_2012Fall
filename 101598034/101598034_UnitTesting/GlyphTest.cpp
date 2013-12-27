#include "gtest\gtest.h"
#include "Glyph.h"

class GlyphTest :
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

// Glyph 無含有邏輯之 function (pure virtual function 不算)