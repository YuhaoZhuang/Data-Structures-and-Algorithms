#include <functional>
#include <gtest/gtest.h>

#include "pqueue.h"

TEST(PQueue, less) {
  PQueue<int> pq;
  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 2);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 23);
}

TEST(PQueue, great) {
  PQueue<int, std::greater<int>> pq;

  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 42);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 34);
}

TEST(PQueue, empty) {
  // Check Top, Pop when empty
  PQueue<int, std::greater<int>> pq;
  EXPECT_EQ(pq.Size(), 0);
  EXPECT_THROW(pq.Pop(), std::exception);
  EXPECT_THROW(pq.Top(), std::exception);
}

TEST(PQueue, Pop_End_less) {
  // Pop Until End and Check Top and Size Each Time
  // Min Heap
  PQueue<int> pq;
  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 2);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 23);
  EXPECT_EQ(pq.Size(), 3);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 34);
  EXPECT_EQ(pq.Size(), 2);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 42);
  EXPECT_EQ(pq.Size(), 1);
  pq.Pop();
  EXPECT_THROW(pq.Pop(), std::exception);
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
}

TEST(PQueue, Pop_End_great) {
  // Pop Until End and Check Top and Size Each Time
  // Max Heap
  PQueue<int, std::greater<int>> pq;
  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 42);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 34);
  EXPECT_EQ(pq.Size(), 3);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 23);
  EXPECT_EQ(pq.Size(), 2);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 2);
  EXPECT_EQ(pq.Size(), 1);
  pq.Pop();
  EXPECT_THROW(pq.Pop(), std::exception);
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
}

TEST(PQueue, Complete_less) {
// Test min heap with complete binary trees
// When first pop, one node will not have any
// siblings
  PQueue<int> pq;
  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);
  pq.Push(60);
  pq.Push(50);
  pq.Push(1);

  EXPECT_EQ(pq.Top(), 1);
  EXPECT_EQ(pq.Size(), 7);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 2);
}

TEST(PQueue, Complete_greater) {
  // Test max heap complete binary trees
  // When first pop, one node will not have any
  // siblings
  PQueue<int, std::greater<int>> pq;
  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);
  pq.Push(50);
  pq.Push(60);
  pq.Push(1);

  EXPECT_EQ(pq.Top(), 60);
  EXPECT_EQ(pq.Size(), 7);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 50);
}

TEST(PQueue, Pop_End_complete_less) {
  // Test min heap with complete binary trees
  // Pop Until End and Check Top and Size Each Time
  PQueue<int> pq;
  pq.Push(42);
  pq.Push(50);
  pq.Push(60);
  pq.Push(1);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 1);
  EXPECT_EQ(pq.Size(), 7);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 2);
  EXPECT_EQ(pq.Size(), 6);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 23);
  EXPECT_EQ(pq.Size(), 5);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 34);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 42);
  EXPECT_EQ(pq.Size(), 3);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 50);
  EXPECT_EQ(pq.Size(), 2);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 60);
  EXPECT_EQ(pq.Size(), 1);
  pq.Pop();
  EXPECT_THROW(pq.Pop(), std::exception);
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
}

TEST(PQueue, Pop_End_complete_great) {
  // Test max heap with complete binary trees
  // Pop Until End and Check Top and Size Each Time
  PQueue<int, std::greater<int>> pq;
  pq.Push(50);
  pq.Push(60);
  pq.Push(1);
  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 60);
  EXPECT_EQ(pq.Size(), 7);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 50);
  EXPECT_EQ(pq.Size(), 6);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 42);
  EXPECT_EQ(pq.Size(), 5);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 34);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 23);
  EXPECT_EQ(pq.Size(), 3);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 2);
  EXPECT_EQ(pq.Size(), 2);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 1);
  EXPECT_EQ(pq.Size(), 1);
  pq.Pop();
  EXPECT_THROW(pq.Pop(), std::exception);
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
}

class MyClass {
 public:
  MyClass(int n) : n_(n) {}
  bool operator < (const MyClass &mc) const { return n_ < mc.n_; }
  int n() { return n_; }
 private:
  int n_;
};

TEST(PQueue, custom_class) {
  std::vector<MyClass> vec{MyClass(42), MyClass(23), MyClass(2), MyClass(34)};

  PQueue<MyClass> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top().n(), vec[2].n());
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top().n(), vec[1].n());
}

class min {
 public:
  bool operator() (const MyClass* x, const MyClass* y) {
    return (*x) < (*y);
  }
};

TEST(PQueue, custom_class_pointer) {
  std::vector<MyClass*> vec{new MyClass(42), new MyClass(23),
                            new MyClass(2), new MyClass(34)};

  PQueue<MyClass*, min> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top(), vec[2]);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), vec[1]);
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
