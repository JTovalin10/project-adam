#include <gtest/gtest.h>

#include "UniquePtr.h"

TEST(uptr, constructor) { slime::unique_ptr<int> ptr; }
