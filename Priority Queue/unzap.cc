#include "bstream.h"
#include "pqueue.h"
#include "huffman.h"

int main(int argc, char *argv[]) {
  if (argv[1] && argv[2]) {
  } else {
    std::cerr << "Usage : ./unzap_reference " <<
      "<zapfile> <outputfile>" << std::endl;
    return 1;
  }
  std::ifstream ifs(argv[1], std::ios::in |
    std::ios::binary);
  if (!ifs) {
    std::cerr << "Error: cannot open input file "
      << argv[1] << std::endl;
    return 1;
  }
  std::ofstream ofs(argv[2]);
  Huffman unzap;
  unzap.Decompress(ifs, ofs);
  std::cout << "Decompressed zap file " << argv[1]
    << " into output file " << argv[2] << std::endl;
  return 0;
}
