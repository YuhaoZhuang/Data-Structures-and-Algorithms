#include "bstream.h"
#include "pqueue.h"
#include "huffman.h"

int main(int argc, char *argv[]) {
  if (argv[1] && argv[2]) {
  } else {
    std::cerr << "Usage: . /zap_reference " <<
      "<inputfile> <zapfile>" << std::endl;
    return 1;
  }
  std::ifstream ifs(argv[1]);
  if (!ifs) {
    std::cerr << "Error: cannot open input file "
      << argv[1] << std::endl;
    return 1;
  }
  std::ofstream ofs(argv[2], std::ios::out |
    std::ios::trunc |
    std::ios::binary);
  Huffman zap;
  std::cout << "Compressed input file " << argv[1]
    << " into zap file " << argv[2] << std::endl;
  zap.Compress(ifs, ofs); 
  ifs.close();
  ofs.close();
  return 0;
}