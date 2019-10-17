#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <array>
#include <cstddef>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cerrno>
#include <map>

#include "bstream.h"
#include "pqueue.h"

class HuffmanNode {
 public:
  explicit HuffmanNode(char ch, size_t freq,
    HuffmanNode* left = nullptr,
    HuffmanNode* right = nullptr)
    : ch_(ch), freq_(freq), left_(left), right_(right) { }


  bool IsLeaf() {
    // Node is a leaf if it doesn't have any children
    return left_ == nullptr && right_ == nullptr;
  }

  bool operator < (const HuffmanNode& n) const {
    // In case of equality, make it deterministic based on character
    if (freq_ == n.freq_)
      return ch_ < n.ch_;
    // Otherwise compare frequencies
    return freq_ < n.freq_;
  }

  size_t freq() { return freq_; }
  size_t data() { return ch_; }
  HuffmanNode* left() { return left_; }
  HuffmanNode* right() { return right_; }

 private:
  char ch_;
  size_t freq_;
  HuffmanNode *left_, *right_;
};

// Comparator for HuffmanNode*
struct Compare {
  bool operator() (const HuffmanNode* node1, const HuffmanNode* node2) {
    return (*node1) < (*node2);
  }
};

class Huffman {
 public:
  static void Compress(std::ifstream& ifs, std::ofstream& ofs);
  static void Decompress(std::ifstream& ifs, std::ofstream& ofs);

 private:
  static std::string GetInput(std::ifstream& fin);
  static void BuildTree(PQueue<HuffmanNode*, Compare>& huff_tree);
  static void OutputTree(HuffmanNode* node, BinaryOutputStream& bos);
  static void DeleteTree(HuffmanNode* node);

  static HuffmanNode* GetNextNode(BinaryInputStream& bis);

  static void GenerateFreqTable(std::map<char, int>& freq,
    std::string& contents);

  static void GenerateCodingTable(HuffmanNode* node, std::string bitstring,
    std::map<char, std::string>& code_table);

  static char GetEncodedChar(HuffmanNode* node, BinaryInputStream& bis);

  static void Print(HuffmanNode* node);
};

void Huffman::Compress(std::ifstream& ifs, std::ofstream& ofs) {
  PQueue<HuffmanNode*, Compare> huff_tree;
  BinaryOutputStream bos(ofs);

  std::string contents = GetInput(ifs);
  std::map<char, int> freq;
  std::map<char, std::string> code_table;

  GenerateFreqTable(freq, contents);

  for (const auto& c : freq) {
    // allocate space for HuffmanNode on heap
    huff_tree.Push(new HuffmanNode(c.first, c.second));
  }


  BuildTree(huff_tree);
  OutputTree(huff_tree.Top(), bos);

  // output number of encoded characters in binary
  bos.PutInt(static_cast<int>(contents.size()));

  GenerateCodingTable(huff_tree.Top(), "", code_table);

  // output the encoding for each character
  for (auto ch : contents)
    // loop through each bit character in bitstring
    for (auto bit : code_table[ch])
      (bit == '1') ? bos.PutBit(1) : bos.PutBit(0);

  DeleteTree(huff_tree.Top());

  bos.Close();        // flush binary stream
  ofs.close();
}

void Huffman::Decompress(std::ifstream& ifs, std::ofstream& ofs) {
  BinaryInputStream bis(ifs);
  BinaryOutputStream bos(ofs);
  std::map<char, std::string> code_table;

  // read in the first bit for the root node
  // if the root is a leaf, only one type of character in file
  if (bis.GetBit()) {
    char ch = bis.GetChar();
    int size = bis.GetInt();

    while (size--)
      bos.PutChar(ch);

    return;
  }


  // reconstruct the huffman tree
  HuffmanNode* root = new HuffmanNode(0, 0, GetNextNode(bis), GetNextNode(bis));

  int size = bis.GetInt();

  // print out all the encoded characters
  while (size--) {
    bos.PutChar(GetEncodedChar(root, bis));
  }


  // read bits from the stream until we find a codeword, then print it
  // loop while we still have characters in the stream
  // (go left if 0 bit, right if 1 bit, output char if we reach leaf node)
  // write character in output file

  // check for memory leaks

  DeleteTree(root);
}


// restructure the priority queue of Huffman leaf nodes into a Huffman tree
void Huffman::BuildTree(PQueue<HuffmanNode*, Compare>& huff_tree) {
  while (huff_tree.Size() != 1) {
    HuffmanNode* node1 = huff_tree.Top();
    huff_tree.Pop();
    HuffmanNode* node2 = huff_tree.Top();
    huff_tree.Pop();

    HuffmanNode* internal_node = new HuffmanNode
    (0, node1->freq() + node2->freq(), node1, node2);
    huff_tree.Push(internal_node);
  }
}

// output the tree in binary format (using pre order traversal)
// each internal node has 2 leaf nodes, so we don't need to check nullptr
void Huffman::OutputTree(HuffmanNode* node, BinaryOutputStream& bos) {
  if (node->data() != 0) {               // leaf node: output '1' and char
    bos.PutBit(1);
    bos.PutChar(node->data());

  } else {                                // internal node
    bos.PutBit(0);
    OutputTree(node->left(), bos);
    OutputTree(node->right(), bos);
  }
}

// delete the nodes of the tree using a post order traversal
void Huffman::DeleteTree(HuffmanNode* node) {
  if (node == nullptr)
    return;

  // recursively delete subtrees, then delete node when going up recursion
  DeleteTree(node->left());
  DeleteTree(node->right());

  delete(node);
}

// recursively reconstruct the Huffman tree from the bitstring,
// by creating new nodes
// and recursively setting the next node node in the list as left/right child
// (the order is correct because huffman tree is given in preorder traversal)
HuffmanNode* Huffman::GetNextNode(BinaryInputStream& bis) {
  if (bis.GetBit()) {       // create leaf node
                            // std::cout << "created leaf node" << std::endl;
    return new HuffmanNode(bis.GetChar(), 0);
  } else {
    // internal node: recursively set left and right children
    // to next node in preorder traversal
    return new HuffmanNode(0, 0, GetNextNode(bis), GetNextNode(bis));
  }
}

void Huffman::GenerateFreqTable(std::map<char, int>& freq,
  std::string& contents) {
  for (unsigned int i = 0; i < contents.size(); i++) {
    // value already exists in map
    if (freq.find(contents[i]) != freq.end())
      freq[contents[i]]++;

    else
      freq[contents[i]] = 1;
  }
}

void Huffman::GenerateCodingTable(HuffmanNode* node, std::string bitstring,
  std::map<char, std::string>& code_table) {
  // store encoding for each leaf node
  if (node->data() != 0) {
    code_table[node->data()] = bitstring;
  } else {
    GenerateCodingTable(node->left(), bitstring + '0', code_table);
    GenerateCodingTable(node->right(), bitstring + '1', code_table);
  }
}

// use the Huffman tree to recursively read in the next encoded
// char from bitstring
// go left if 0 bit, go right if 1 bit, return the char when we read the node
// huffman codes are unique by prefix
char Huffman::GetEncodedChar(HuffmanNode* node, BinaryInputStream& bis) {
  if (node->data() != 0)                   // leaf node
    return node->data();

  if (bis.GetBit())                        // go right if bit is 1
    return GetEncodedChar(node->right(), bis);

  else                                    // go left
    return GetEncodedChar(node->left(), bis);
}

// reads the input file into a string
std::string Huffman::GetInput(std::ifstream& fin) {
  if (fin) {
    std::string contents;
    fin.seekg(0, std::ios::end);
    contents.resize(fin.tellg());                 // get length of the file
    fin.seekg(0, std::ios::beg);
    fin.read(&contents[0], contents.size());      // read data as a block

    fin.close();
    return(contents);
  }
  throw(errno);
}

// print function for debugging purposes
void Huffman::Print(HuffmanNode* node) {
  if (node == nullptr)
    return;

  if (node->data() == 0)               // internal node
    std::cout << node->data();

  else
    std::cout << static_cast<char>(node->data());

  std::cout << " " << node->freq() << std::endl;

  Print(node->left());
  Print(node->right());
}

#endif  // HUFFMAN_H_
