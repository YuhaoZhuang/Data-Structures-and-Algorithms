#include "deque.h"
#include <gtest/gtest.h> // NOLINT (build/c++11)

TEST(Deque, Empty) {
  Deque<int> dq;

  /* Should be fully empty */
  EXPECT_EQ(dq.Empty(), true);
  EXPECT_EQ(dq.Size(), 0);
  EXPECT_THROW(dq.PopFront(), std::exception);
}

TEST(Deque, DoubleInsertionBack) {
  Deque<int> dq;
  /* Test some insertion */
  // Test Push Back at beginning, end of array
  dq.PushBack(23);
  dq.PushBack(42);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq.Back(), 42);
}


TEST(Deque, EndPushFront) {
  Deque<int> dq;
  /* Test some insertion */
  // Test Push Front at end of array
  dq.PushBack(23);
  dq.PushFront(42);
  dq.PushFront(74);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 3);
  EXPECT_EQ(dq[0], 74);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq[2], 23);
  EXPECT_EQ(dq.Front(), 74);
  EXPECT_EQ(dq.Back(), 23);
}

TEST(Deque, MidPushBack) {
  Deque<int> dq;
  /* Test some insertion */
  // Test Push Back at middle of array
  dq.PushBack(23);
  dq.PushFront(42);
  dq.PushBack(74);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 3);
  EXPECT_EQ(dq[0], 42);
  EXPECT_EQ(dq[1], 23);
  EXPECT_EQ(dq[2], 74);
  EXPECT_EQ(dq.Front(), 42);
  EXPECT_EQ(dq.Back(), 74);
}

TEST(Deque, MiddlePushFront_Resize) {
  Deque<int> dq;
  // Test Push Front at middle of array
  // Need to resize first
  dq.PushBack(23);
  dq.PushFront(42);
  dq.PushFront(74);
  dq.PushFront(91);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq[0], 91);
  EXPECT_EQ(dq[1], 74);
  EXPECT_EQ(dq[2], 42);
  EXPECT_EQ(dq[3], 23);
  EXPECT_EQ(dq.Front(), 91);
  EXPECT_EQ(dq.Back(), 23);
}

TEST(Deque, MiddlePushBack_Resize) {
  Deque<int> dq;
  // Test Push Back at middle of array
  // need to resize first
  dq.PushBack(23);
  dq.PushFront(42);
  dq.PushBack(74);
  dq.PushBack(103);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq[0], 42);
  EXPECT_EQ(dq[1], 23);
  EXPECT_EQ(dq[2], 74);
  EXPECT_EQ(dq[3], 103);
  EXPECT_EQ(dq.Front(), 42);
  EXPECT_EQ(dq.Back(), 103);
}

TEST(Deque, PushBack_Tail_Begin) {
  Deque<int> dq;
  // Test PushBack when tail at beginning
  // Need to Resize first
  dq.PushFront(23);
  dq.PushFront(42);
  dq.PushFront(43);
  dq.PushBack(32);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq[0], 43);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq[2], 23);
  EXPECT_EQ(dq[3], 32);
  EXPECT_EQ(dq.Back(), 32);
  EXPECT_EQ(dq.Front(), 43);
}

TEST(Deque, PushBack_Tail_End) {
  Deque<int> dq;
  // Test PushBack when tail at end of array
  // Need to resize first
  dq.PushBack(23);
  dq.PushBack(42);
  dq.PushBack(43);
  dq.PushBack(32);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq[2], 43);
  EXPECT_EQ(dq[3], 32);
  EXPECT_EQ(dq.Back(), 32);
  EXPECT_EQ(dq.Front(), 23);
}

TEST(Deque, PushBack_Reisze_UseFront) {
  Deque<int> dq;
  // Test PushFront when tail at end of array,
  // head at beginning
  // need to resize first
  dq.PushBack(23);
  dq.PushBack(42);
  dq.PushBack(43);
  dq.PushFront(32);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq[0], 32);
  EXPECT_EQ(dq[1], 23);
  EXPECT_EQ(dq[2], 42);
  EXPECT_EQ(dq[3], 43);
  EXPECT_EQ(dq.Back(), 43);
  EXPECT_EQ(dq.Front(), 32);
}

TEST(Deque, PopFront_HeadAtEnd) {
  Deque<int> dq;
  // Test PopFront when head is at end
  // Spaces in between (circular array)
  dq.PushFront(23);
  dq.PushFront(42);
  dq.PushBack(13);
  dq.PushBack(20);
  dq.PopFront();
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 3);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq[1], 13);
  EXPECT_EQ(dq[2], 20);
  EXPECT_EQ(dq.Front(), 23);
  EXPECT_EQ(dq.Back(), 20);
}

TEST(Deque, PopFront_HeadAtFront) {
  Deque<int> dq;
  // Test PopFront when head is at front
  // Spaces in between (circular array)
  dq.PushFront(23);
  dq.PushBack(42);
  dq.PushBack(13);
  dq.PushBack(10);
  dq.PopFront();
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 3);
  EXPECT_EQ(dq[0], 42);
  EXPECT_EQ(dq[1], 13);
  EXPECT_EQ(dq[2], 10);
  EXPECT_EQ(dq.Front(), 42);
  EXPECT_EQ(dq.Back(), 10);
}

TEST(Deque, PopFront_HeadAtMid) {
  Deque<int> dq;
  // Test PopFront when head is at front
  // Spaces in between (circular array)
  dq.PushFront(23);
  dq.PushFront(42);
  dq.PushFront(13);
  dq.PushBack(10);
  dq.PopFront();
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 3);
  EXPECT_EQ(dq[0], 42);
  EXPECT_EQ(dq[1], 23);
  EXPECT_EQ(dq[2], 10);
  EXPECT_EQ(dq.Front(), 42);
  EXPECT_EQ(dq.Back(), 10);
}

TEST(Deque, PopBack_TailAtEnd) {
  Deque<int> dq;
  // Test PopFront when head is at front
  // Resized array
  dq.PushFront(23);
  dq.PushBack(10);
  dq.PushBack(21);
  dq.PushBack(31);
  dq.PopBack();
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 3);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq[1], 10);
  EXPECT_EQ(dq[2], 21);
  EXPECT_EQ(dq.Front(), 23);
  EXPECT_EQ(dq.Back(), 21);
}

TEST(Deque, PopBack_TailAtFront) {
  Deque<int> dq;
  // Test PopFront when tail is at front
  // Resized array
  dq.PushBack(23);
  dq.PushFront(10);
  dq.PushFront(21);
  dq.PushFront(31);
  dq.PopBack();
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 3);
  EXPECT_EQ(dq[0], 31);
  EXPECT_EQ(dq[1], 21);
  EXPECT_EQ(dq[2], 10);
  EXPECT_EQ(dq.Front(), 31);
  EXPECT_EQ(dq.Back(), 10);
}

TEST(Deque, PopFrontBeginning_PushBack) {
  Deque<int> dq;
  // Test Push Back when front being poped and != 0
  // Should wrap around (circular array)
  dq.PushFront(23);
  dq.PushBack(42);
  dq.PushBack(43);
  dq.PopFront();
  dq.PushBack(32);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 3);
  EXPECT_EQ(dq[0], 42);
  EXPECT_EQ(dq[1], 43);
  EXPECT_EQ(dq[2], 32);
  EXPECT_EQ(dq.Back(), 32);
  EXPECT_EQ(dq.Front(), 42);
  dq.PushFront(29);
  EXPECT_EQ(dq.Front(), 29);
  EXPECT_EQ(dq[0], 29);
}


TEST(Deque, PopFrontBeginning_PushFront) {
  Deque<int> dq;
  // Test Push Front wen front being popped and !=0
  // Test Circular array
  dq.PushFront(23);
  dq.PushFront(42);
  dq.PushFront(43);
  dq.PopFront();
  dq.PushBack(32);
  dq.PushFront(109);
  dq.PushBack(72);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 5);
  EXPECT_EQ(dq[0], 109);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq[2], 23);
  EXPECT_EQ(dq[3], 32);
  EXPECT_EQ(dq[4], 72);
  EXPECT_EQ(dq.Back(), 72);
  EXPECT_EQ(dq.Front(), 109);
  dq.PushFront(29);
  EXPECT_EQ(dq.Front(), 29);
  dq.PushBack(101);
  EXPECT_EQ(dq.Back(), 101);
}


TEST(Deque, PopFrontToEnd) {
  Deque<int> dq;
  // Test PopFront All the way to End
  dq.PushBack(23);
  dq.PushBack(42);
  dq.PushBack(43);
  dq.PopFront();
  dq.PushBack(32);
  dq.PushFront(109);
  dq.PushBack(72);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 5);
  EXPECT_EQ(dq[0], 109);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq[2], 43);
  EXPECT_EQ(dq[3], 32);
  EXPECT_EQ(dq[4], 72);
  EXPECT_EQ(dq.Back(), 72);
  EXPECT_EQ(dq.Front(), 109);
  dq.PushFront(29);
  EXPECT_EQ(dq.Front(), 29);
  dq.PushBack(101);
  EXPECT_EQ(dq.Back(), 101);
  EXPECT_EQ(dq.Size(), 7);
  for (auto i = 0; i < 7; i++) {
    dq.PopFront();
  }
  EXPECT_THROW(dq[0], std::exception);
}

TEST(Deque, PopBackToEnd) {
  Deque<int> dq;
  // Test PopBack all the way to end
  // Skips to check the inputs because same
  // as previous
  dq.PushBack(23);
  dq.PushBack(42);
  dq.PushBack(43);
  dq.PopFront();
  dq.PushBack(32);
  dq.PushFront(109);
  dq.PushBack(72);
  dq.PushFront(29);
  dq.PushBack(101);
  EXPECT_EQ(dq.Back(), 101);
  EXPECT_EQ(dq.Size(), 7);
  for (auto i = 0; i < 7; i++) {
    dq.PopBack();
  }
  EXPECT_THROW(dq[0], std::exception);
}

TEST(Deque, ShrinkToFit_SingleLeft) {
  Deque<int> dq;
  // Test ShrinkToFit when there is one
  // element left
  dq.PushBack(23);
  dq.PushBack(42);
  dq.PushBack(43);
  dq.PopFront();
  dq.PushBack(32);
  dq.PushFront(109);
  dq.PushBack(72);
  dq.PushFront(29);
  dq.PushBack(101);
  for (auto i = 0; i < 6; i++) {
    dq.PopBack();
  }
  EXPECT_EQ(dq.Front(), 29);
  dq.ShrinkToFit();
  EXPECT_EQ(dq.Size(), 1);
  EXPECT_EQ(dq.Front(), 29);
  EXPECT_EQ(dq[0], 29);
  EXPECT_THROW(dq[1], std::exception);
}

TEST(Deque, ShrinkToFit_MultipleLeft) {
  Deque<int> dq;
  // Test ShrinkToFit when there is one
  // element left
  dq.PushFront(12);
  dq.PushFront(14);
  dq.PushFront(17);
  dq.PushBack(42);
  dq.PushBack(43);
  dq.PushBack(32);
  dq.PushBack(109);
  dq.PushBack(72);
  dq.PushBack(29);
  dq.PushBack(101);
  dq.PushBack(122);
  dq.PushBack(21);
  dq.PushBack(45);
  dq.PopFront();
  for (auto i = 0; i <9 ; i++) {
    dq.PopBack();
  }
  EXPECT_EQ(dq.Size(), 3);
  dq.ShrinkToFit();
  EXPECT_EQ(dq.Front(), 14);
  EXPECT_EQ(dq.Back(), 42);
  EXPECT_EQ(dq[0], 14);
  EXPECT_EQ(dq[1], 12);
  EXPECT_EQ(dq[2], 42);
}

TEST(Deque, Random4) {
  Deque<int> dq;
  // Random 4 insertiong and pop
  dq.PushBack(23);
  dq.PushFront(42);
  dq.PushFront(74);
  dq.PushBack(33);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq[0], 74);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq[2], 23);
  EXPECT_EQ(dq[3], 33);
  EXPECT_EQ(dq.Front(), 74);
  EXPECT_EQ(dq.Back(), 33);
  dq.PopBack();
  dq.PopFront();
  dq.PopFront();
  EXPECT_EQ(dq.Size(), 1);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq.Front(), 23);
  EXPECT_EQ(dq.Back(), 23);
}

TEST(Deque, Random4_1) {
  Deque<int> dq;
  // Random 4 insertiong and pop
  dq.PushFront(42);
  dq.PushBack(23);
  dq.PushFront(74);
  dq.PushBack(33);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq[0], 74);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq[2], 23);
  EXPECT_EQ(dq[3], 33);
  EXPECT_EQ(dq.Front(), 74);
  EXPECT_EQ(dq.Back(), 33);
  dq.PopBack();
  dq.PopFront();
  dq.PopFront();
  EXPECT_EQ(dq.Size(), 1);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq.Front(), 23);
  EXPECT_EQ(dq.Back(), 23);
}

TEST(Deque, Random4_2) {
  Deque<int> dq;
  // Random 4 insertiong and pop
  dq.PushFront(42);
  dq.PushBack(23);
  dq.PushFront(74);
  dq.PushBack(33);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq[0], 74);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq[2], 23);
  EXPECT_EQ(dq[3], 33);
  EXPECT_EQ(dq.Front(), 74);
  EXPECT_EQ(dq.Back(), 33);
  dq.PopFront();
  dq.PopFront();
  dq.PopBack();
  EXPECT_EQ(dq.Size(), 1);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq.Front(), 23);
  EXPECT_EQ(dq.Back(), 23);
}



int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

