#include "stdafx.h"
#include "MemoryLeakDetector.h"

TEST(TestBuild, ShouldAlwaysBeInDebug)
{
#ifndef _DEBUG
  FAIL() << "Always compile in _DEBUG mode to detect memory leaks";
#endif
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  UnitTest::GetInstance()->listeners().Append(new MemoryLeakDetector());
  return RUN_ALL_TESTS();
}
