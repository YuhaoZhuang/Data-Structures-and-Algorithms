#include <cstdio>
#include <fstream>

#include <gtest/gtest.h>

#include "bstream.h"

TEST(BStream, input) {
  std::string filename{ "test_bstream_input" };

  const unsigned char val[] = {
    0x58, 0x90, 0xab, 0x08,
    0x00, 0x4e, 0xdb, 0x40,
  };
  // Equivalent in binary is:
  // 0101100010010000101010110000100000000000010011101101101101000000
  // ^5  ^8  ^9  ^0  ^a  ^b  ^0  ^8  ^0  ^0  ^4  ^e  ^d  ^b  ^4  ^0
  // Write this to a file
  std::ofstream ofs(filename, std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  ofs.write(reinterpret_cast<const char *>(val), sizeof(val));
  ofs.close();

  // Read it back in binary format
  std::ifstream ifs(filename, std::ios::in |
    std::ios::binary);
  BinaryInputStream bis(ifs);

  // Make sure that we reading the binary in the correct order
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetChar(), 0x62); // 01100010
  EXPECT_EQ(bis.GetChar(), 0x42); // 01000010
  EXPECT_EQ(bis.GetBit(), 1);
  //EXPECT_EQ(bis.GetInt(), 0x58400276); // 01011000010000000000001001110110

  // last 3 bits truncated: which means throws exception if uncommenting last eq

  ifs.close();

  std::remove(filename.c_str());
}

TEST(BStream, output) {
  std::string filename{ "test_bstream_output" };
  std::ofstream ofs(filename, std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  BinaryOutputStream bos(ofs);

  bos.PutBit(1);
  bos.PutBit(0);
  bos.PutChar(0xfe);
  bos.PutChar(0x63);
  bos.PutBit(0);
  bos.PutInt(0x28054b73);

  bos.Close();
  ofs.close();

  // Read it back in binary format
  std::ifstream ifs(filename, std::ios::in |
    std::ios::binary);
  BinaryInputStream bis(ifs);

  // Make sure that we reading the binary in the correct order
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0xfe);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x63);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetInt(), 0x28054b73);

  ifs.close();
  std::remove(filename.c_str());
}

// All the following tests writes to the output file using
// binaryoutputstream, then reads it back in using
// binaryinputstream, so checks both programs at the same time

TEST(BStream, empty) {
  // test empty file
  std::string filename{ "test_space_line" };
  std::ofstream ofs(filename, std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  BinaryOutputStream bos(ofs);
  bos.Close();
  ofs.close();

  std::ifstream ifs(filename, std::ios::in |
    std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_THROW((unsigned char)bis.GetChar(), std::exception);
  EXPECT_THROW(bis.GetInt(), std::exception);
  EXPECT_THROW(bis.GetBit(), std::exception);
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, space) {
  // test if reading and writing spaces correctly
  std::string filename{ "test_space" };
  std::ofstream ofs(filename, std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  BinaryOutputStream bos(ofs);
  bos.PutChar(' ');
  bos.PutChar(' ');
  bos.PutChar(' ');
  bos.PutChar(' ');
  bos.Close();
  ofs.close();

  std::ifstream ifs(filename, std::ios::in |
    std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x20);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x20);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x20);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x20);
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, newline) {
  // test new lines
  std::string filename{ "test_newline" };
  std::ofstream ofs(filename, std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  BinaryOutputStream bos(ofs);
  bos.PutChar('\n');
  bos.PutChar('\n');
  bos.PutChar('\n');
  bos.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in |
    std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x0A);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x0A);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x0A);
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, tabs) {
  // Test tabs
  std::string filename{ "test_tabs" };
  std::ofstream ofs(filename, std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  BinaryOutputStream bos(ofs);
  bos.PutChar('\t');
  bos.PutChar('\t');
  bos.PutChar('\t');
  bos.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in |
    std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x9);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x9);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x9);
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, space_line_tab) {
  // test space, tab, new lines
  std::string filename{ "test_space_line_tab" };
  std::ofstream ofs(filename, std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  BinaryOutputStream bos(ofs);

  bos.PutChar(' ');
  bos.PutChar(' ');
  bos.PutChar(' ');
  bos.PutChar(' ');
  bos.PutChar('\n');
  bos.PutChar('\t');
  bos.PutChar('\t');
  bos.PutChar(' ');
  bos.PutChar('\n');
  bos.Close();
  ofs.close();

  std::ifstream ifs(filename, std::ios::in |
    std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x20);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x20);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x20);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x20);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x0A);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x9);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x9);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x20);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x0A);
  EXPECT_THROW((unsigned char)bis.GetChar(), std::exception);
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, spcial) {
  // test special characters
  std::string filename{ "test_special" };
  std::ofstream ofs(filename, std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  BinaryOutputStream bos(ofs);

  bos.PutChar('!');
  bos.PutChar('#');
  bos.PutChar('&');
  bos.PutChar('(');

  bos.Close();
  ofs.close();

  std::ifstream ifs(filename, std::ios::in |
    std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x21);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x23);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x26);
  EXPECT_EQ((unsigned char)bis.GetChar(), (unsigned char)0x28);
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, bit) {
  // test special bits
  std::string filename{ "test_bits" };
  std::ofstream ofs(filename, std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  BinaryOutputStream bos(ofs);

  bos.PutBit(1);
  bos.PutBit(1);
  bos.PutBit(0);
  bos.PutBit(1);
  bos.PutBit(0);

  bos.Close();
  ofs.close();

  std::ifstream ifs(filename, std::ios::in |
    std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_THROW(bis.GetChar(), std::exception);
  ifs.close();
  std::remove(filename.c_str());
}


TEST(BStream, test_int) {
  // check int
  std::string filename{ "test_int" };
  std::ofstream ofs(filename, std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  BinaryOutputStream bos(ofs);

  bos.PutInt(324);
  bos.PutInt(548);
  bos.PutInt(12);
  bos.PutInt(0);
  bos.PutInt(1);

  bos.Close();
  ofs.close();

  std::ifstream ifs(filename, std::ios::in |
    std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetInt(), 324);
  EXPECT_EQ(bis.GetInt(), 548);
  EXPECT_EQ(bis.GetInt(), 12);
  EXPECT_EQ(bis.GetInt(), 0);
  EXPECT_EQ(bis.GetInt(), 1);
  EXPECT_THROW(bis.GetInt(), std::exception);
  ifs.close();
  std::remove(filename.c_str());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
