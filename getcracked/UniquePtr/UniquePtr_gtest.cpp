#include <gtest/gtest.h>

#include <string>

#include "UniquePtr.h"

// A helper class to track if the object was deleted
class DestructorTracker {
 public:
  static int count;
  DestructorTracker() { count++; }
  ~DestructorTracker() { count--; }
};
int DestructorTracker::count = 0;

// A class with multiple arguments to test Perfect Forwarding
class Widget {
 public:
  std::string name;
  int value;
  Widget(std::string n, int v) : name(std::move(n)), value(v) {}
};

// --- Tests ---

TEST(UniquePtrTest, BasicConstruction) {
  slime::unique_ptr<int> ptr(new int(10));
  EXPECT_TRUE(ptr.is_owning());
  EXPECT_EQ(*ptr, 10);
}

TEST(UniquePtrTest, MakeUniqueForwarding) {
  // This tests your make_unique with multiple arguments
  auto ptr = slime::make_unique<Widget>("TestWidget", 42);

  EXPECT_EQ(ptr->name, "TestWidget");
  EXPECT_EQ(ptr->value, 42);
}

TEST(UniquePtrTest, MoveSemantics) {
  auto ptr1 = slime::make_unique<int>(100);
  slime::unique_ptr<int> ptr2 = std::move(ptr1);

  EXPECT_FALSE(ptr1.is_owning());  // ptr1 should be null
  EXPECT_TRUE(ptr2.is_owning());   // ptr2 should have the data
  EXPECT_EQ(*ptr2, 100);
}

TEST(UniquePtrTest, ResourceCleanup) {
  DestructorTracker::count = 0;
  {
    auto ptr = slime::make_unique<DestructorTracker>();
    EXPECT_EQ(DestructorTracker::count, 1);
  }  // ptr goes out of scope here
  EXPECT_EQ(DestructorTracker::count, 0);  // Should be deleted
}

TEST(UniquePtrTest, ResetFunctionality) {
  auto ptr = slime::make_unique<int>(10);
  ptr.reset(new int(20));
  EXPECT_EQ(*ptr, 20);
}

TEST(UniquePtrTest, ReleaseFunctionality) {
  auto ptr = slime::make_unique<int>(50);
  int* raw = ptr.release();

  EXPECT_FALSE(ptr.is_owning());
  EXPECT_EQ(*raw, 50);

  delete raw;  // We took ownership, so we must delete manually
}
