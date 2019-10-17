#include <gtest/gtest.h>
#include "treemap.h"

TEST(Treemap, Empty) {
  Treemap<int, int> map;

  /* Should be fully empty */
  EXPECT_EQ(map.Empty(), true);
  EXPECT_EQ(map.Size(), 0);
  EXPECT_THROW(map.Get(42), std::exception);
}

TEST(Treemap, OneKey) {
  Treemap<int, char> map;
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 2);
  EXPECT_EQ(map.MinKey(), 23);
  EXPECT_EQ(map.MaxKey(), 42);
  EXPECT_EQ(map.Get(23), 'A');
  EXPECT_THROW(map.Get(30), std::exception);
}

TEST(Treemap, Empty_call) {
  // Test Methods under empty condition
  Treemap<int, char> map;
  EXPECT_THROW(map.Get(30), std::exception);
  EXPECT_EQ(map.ContainsKey(30), false);
  EXPECT_EQ(map.ContainsValue('A'), false);
  EXPECT_THROW(map.MaxKey(), std::exception);
  EXPECT_THROW(map.MinKey(), std::exception);
  EXPECT_THROW(map.CeilKey(31), std::exception);
  EXPECT_THROW(map.FloorKey(56), std::exception);
}

TEST(Treemap, ContainsKey) {
  // Test ContainsKey function
  Treemap<int, char> map;
  EXPECT_EQ(map.ContainsKey(23), false);
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  map.Insert(37, 'C');
  map.Insert(10, 'D');
  EXPECT_EQ(map.ContainsKey(23), true);
  EXPECT_EQ(map.ContainsKey(42), true);
  EXPECT_EQ(map.ContainsKey(37), true);
  EXPECT_EQ(map.ContainsKey(10), true);
  EXPECT_EQ(map.ContainsKey(32), false);
  EXPECT_EQ(map.ContainsKey(77), false);
  EXPECT_EQ(map.Size(), 4);
}

TEST(Treemap, ContainsValue) {
  // Test ContainsValue function
  Treemap<int, char> map;
  EXPECT_EQ(map.ContainsValue('A'), false);
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  map.Insert(37, 'C');
  map.Insert(10, 'D');
  map.Insert(100, 'E');
  map.Insert(1000, 'E');
  map.Insert(500, 'E');
  EXPECT_EQ(map.ContainsValue('A'), true);
  EXPECT_EQ(map.ContainsValue('B'), true);
  EXPECT_EQ(map.ContainsValue('C'), true);
  EXPECT_EQ(map.ContainsValue('D'), true);
  EXPECT_EQ(map.ContainsValue('E'), true);
  EXPECT_EQ(map.ContainsValue('Z'), false);
  EXPECT_EQ(map.Size(), 7);
}

TEST(Treemap, GetValue) {
  // Test ContainsValue function
  Treemap<int, char> map;
  EXPECT_THROW(map.Get(23), std::exception);
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  map.Insert(37, 'C');
  map.Insert(10, 'D');
  map.Insert(100, 'E');
  map.Insert(1000, 'E');
  EXPECT_EQ(map.Size(), 6);
  EXPECT_EQ(map.Get(23), 'A');
  EXPECT_EQ(map.Get(42), 'B');
  EXPECT_EQ(map.Get(37), 'C');
  EXPECT_EQ(map.Get(10), 'D');
  EXPECT_EQ(map.Get(100), 'E');
  EXPECT_EQ(map.Get(1000), 'E');
}

TEST(Treemap, Remove_UntilEnd) {
  // Test Remove until end and other functions
  Treemap<int, char> map;
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  map.Remove(42);
  EXPECT_EQ(map.Size(), 1);
  EXPECT_EQ(map.Get(23), 'A');
  EXPECT_THROW(map.Get(30), std::exception);
  EXPECT_EQ(map.MinKey(), 23);
  EXPECT_EQ(map.MaxKey(), 23);
  map.Remove(23);
  // Empty
  EXPECT_EQ(map.Empty(), true);
  EXPECT_EQ(map.Size(), 0);
  // Remove throw exception when none;
  EXPECT_THROW(map.Remove(9), std::exception);
  EXPECT_EQ(map.ContainsKey(19), false);
  EXPECT_EQ(map.ContainsValue('A'), false);
  // Get throw exception when none;
  EXPECT_THROW(map.Get(19), std::exception);
  map.Insert(30 , 'C');
  EXPECT_EQ(map.Size(), 1);
  EXPECT_EQ(map.MaxKey(), 30);
  EXPECT_EQ(map.MinKey(), 30);
}

TEST(Treemap, Remove_OneEnd) {
  // Remove when node has one child
  Treemap<int, char> map;
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  map.Insert(45, 'C');
  map.Remove(45);
  EXPECT_EQ(map.Size(), 2);
  EXPECT_EQ(map.MinKey(), 23);
  EXPECT_EQ(map.MaxKey(), 42);
  EXPECT_EQ(map.Get(23), 'A');
  EXPECT_EQ(map.Get(42), 'B');
  EXPECT_EQ(map.ContainsKey(45), false);
  EXPECT_EQ(map.ContainsValue('C'), false);
}

TEST(Treemap, Remove_BothEnd) {
  // Remove when node has both child
  Treemap<int, char> map;
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  map.Insert(45, 'C');
  map.Insert(43, 'D');
  map.Remove(43);
  EXPECT_EQ(map.Size(), 3);
  EXPECT_EQ(map.MinKey(), 23);
  EXPECT_EQ(map.MaxKey(), 45);
  EXPECT_EQ(map.Get(23), 'A');
  EXPECT_EQ(map.Get(42), 'B');
  EXPECT_EQ(map.Get(45), 'C');
  EXPECT_EQ(map.ContainsKey(43), false);
  EXPECT_EQ(map.ContainsValue('D'), false);
}

TEST(Treemap, RemoveRoot) {
  // Test Removing of root
  Treemap<int, char> map;
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  map.Insert(11, 'C');
  map.Insert(31, 'D');
  map.Insert(56, 'E');
  map.Insert(28, 'E');
  map.Insert(40, 'F');
  map.Insert(45, 'G');
  map.Insert(61, 'H');
  EXPECT_EQ(map.Size(), 9);
  map.Remove(23);
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 8);
  EXPECT_EQ(map.ContainsKey(23), false);
  EXPECT_EQ(map.ContainsValue('A'), false);
  EXPECT_EQ(map.Get(42), 'B');
  EXPECT_EQ(map.MaxKey(), 61);
  EXPECT_EQ(map.MinKey(), 11);
  EXPECT_THROW(map.Get(30), std::exception);;
}

TEST(Treemap, Remove_Empty_call) {
  // Remove elements until end
  // and Test function calls
  Treemap<int, char> map;
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  map.Remove(23);
  map.Remove(42);
  EXPECT_THROW(map.Get(30), std::exception);
  EXPECT_EQ(map.ContainsKey(30), false);
  EXPECT_EQ(map.ContainsValue('A'), false);
  EXPECT_THROW(map.MaxKey(), std::exception);
  EXPECT_THROW(map.MinKey(), std::exception);
  EXPECT_THROW(map.CeilKey(31), std::exception);
  EXPECT_THROW(map.FloorKey(56), std::exception);
}

TEST(Treemap, FloorKey) {
  // Test some floorkey
  Treemap<int, char> map;
  map.Insert(119, 'A');
  map.Insert(100, 'B');
  map.Insert(130, 'C');
  map.Insert(125, 'D');
  map.Insert(140, 'E');
  map.Insert(135, 'F');
  map.Insert(128, 'G');
  EXPECT_EQ(map.FloorKey(137), 135);
  EXPECT_EQ(map.FloorKey(120), 119);
  EXPECT_EQ(map.FloorKey(129), 128);
  EXPECT_EQ(map.FloorKey(127), 125);
  EXPECT_EQ(map.FloorKey(140), 140);
  EXPECT_EQ(map.FloorKey(141), 140);
  EXPECT_EQ(map.FloorKey(101), 100);
  EXPECT_THROW(map.FloorKey(10), std::exception);
}

TEST(Treemap, Complete_Floorkey) {
  // Test some complete binary tree's
  // Floorkey
  Treemap<int, char> map;
  map.Insert(119, 'A');
  map.Insert(100, 'B');
  map.Insert(130, 'C');
  map.Insert(125, 'D');
  map.Insert(140, 'E');
  map.Insert(56, 'F');
  EXPECT_EQ(map.Size(), 6);
  EXPECT_EQ(map.MinKey(), 56);
  EXPECT_EQ(map.MaxKey(), 140);
  EXPECT_EQ(map.FloorKey(60), 56);
  EXPECT_EQ(map.FloorKey(110), 100);
  EXPECT_EQ(map.FloorKey(120), 119);
  EXPECT_EQ(map.FloorKey(126), 125);
  EXPECT_EQ(map.FloorKey(130), 130);
  EXPECT_EQ(map.FloorKey(131), 130);
  EXPECT_EQ(map.FloorKey(180), 140);
  EXPECT_THROW(map.FloorKey(10), std::exception);
}

TEST(Treemap, Perfect_FloorKey) {
  // Test floorkey perfect binary tree
  Treemap<int, char> map;
  map.Insert(100, 'A');
  map.Insert(50, 'B');
  map.Insert(150, 'C');
  map.Insert(125, 'D');
  map.Insert(160, 'E');
  map.Insert(30, 'F');
  map.Insert(70, 'G');
  EXPECT_EQ(map.Size(), 7);
  EXPECT_EQ(map.MinKey(), 30);
  EXPECT_EQ(map.MaxKey(), 160);
  EXPECT_EQ(map.FloorKey(120), 100);
  EXPECT_EQ(map.FloorKey(170), 160);
  EXPECT_EQ(map.FloorKey(130), 125);
  EXPECT_EQ(map.FloorKey(153), 150);
  EXPECT_EQ(map.FloorKey(60), 50);
  EXPECT_EQ(map.FloorKey(33), 30);
  EXPECT_EQ(map.FloorKey(71), 70);
  EXPECT_THROW(map.FloorKey(10), std::exception);
}

TEST(Treemap, CeilKey) {
  // Test some ceilkey
  Treemap<int, char> map;
  map.Insert(119, 'A');
  map.Insert(100, 'B');
  map.Insert(130, 'C');
  map.Insert(125, 'D');
  map.Insert(140, 'E');
  map.Insert(135, 'F');
  map.Insert(128, 'G');
  EXPECT_EQ(map.CeilKey(132), 135);
  EXPECT_EQ(map.CeilKey(115), 119);
  EXPECT_EQ(map.CeilKey(126), 128);
  EXPECT_EQ(map.CeilKey(124), 125);
  EXPECT_EQ(map.CeilKey(137), 140);
  EXPECT_EQ(map.CeilKey(140), 140);
  EXPECT_EQ(map.CeilKey(90), 100);
  EXPECT_THROW(map.CeilKey(200), std::exception);
}

TEST(Treemap, Complete_CeilKey) {
  // Test some ceilkey in complete
  // binary tree
  Treemap<int, char> map;
  map.Insert(119, 'A');
  map.Insert(100, 'B');
  map.Insert(130, 'C');
  map.Insert(125, 'D');
  map.Insert(140, 'E');
  map.Insert(56, 'F');
  EXPECT_EQ(map.Size(), 6);
  EXPECT_EQ(map.MinKey(), 56);
  EXPECT_EQ(map.MaxKey(), 140);
  EXPECT_EQ(map.CeilKey(50), 56);
  EXPECT_EQ(map.CeilKey(97), 100);
  EXPECT_EQ(map.CeilKey(110), 119);
  EXPECT_EQ(map.CeilKey(122), 125);
  EXPECT_EQ(map.CeilKey(125), 125);
  EXPECT_EQ(map.CeilKey(127), 130);
  EXPECT_EQ(map.CeilKey(135), 140);
  EXPECT_THROW(map.CeilKey(180), std::exception);
}

TEST(Treemap, Perfect_CeilKey) {
  // Test floorkey perfect binary tree
  Treemap<int, char> map;
  map.Insert(100, 'A');
  map.Insert(50, 'B');
  map.Insert(150, 'C');
  map.Insert(125, 'D');
  map.Insert(160, 'E');
  map.Insert(30, 'F');
  map.Insert(70, 'G');
  EXPECT_EQ(map.Size(), 7);
  EXPECT_EQ(map.MinKey(), 30);
  EXPECT_EQ(map.MaxKey(), 160);
  EXPECT_EQ(map.CeilKey(20), 30);
  EXPECT_EQ(map.CeilKey(45), 50);
  EXPECT_EQ(map.CeilKey(64), 70);
  EXPECT_EQ(map.CeilKey(90), 100);
  EXPECT_EQ(map.CeilKey(123), 125);
  EXPECT_EQ(map.CeilKey(134), 150);
  EXPECT_EQ(map.CeilKey(154), 160);
  EXPECT_THROW(map.CeilKey(190), std::exception);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

