#include <iostream>
#include <fstream>
#include "deque.h"

int main(int argc, char *argv[]) {
  // Test to see if number of arguments given are correct
  if (argv[1] && argv[2]) {
  } else {
    std::cerr << "Usage: ./plane_boarding <input_file> <fclass_cap>"
    <<std::endl;
    return 1;
  }
  std::string str = argv[2];
  // Temporary string to test out if second argument is an integer
  for (char& c : str) {
    if (!isdigit(c)) {
      std::cerr << "Error: invalid first class capacity" << std::endl;
      return 1;
    }
  }
  std::ifstream passenger(argv[1]);
  int first_class = atoi(argv[2]);
  // Check to see if file can be opened and if second argument is valid
  if (!passenger) {
    std::cerr << "Error: cannot open file " << argv[1] << std::endl;
    return 1;
  } else if (first_class <= 0) {
    std::cerr << "Error: invalid first class capacity" << std::endl;
    return 1;
  }
  Deque<int> seats;
  // Temporary integer for reading in the file
  int a;
  // Push back if first class, push front if not
  while (passenger >> a) {
    if (a <= first_class) {
      seats.PushBack(a);
    } else {
      seats.PushFront(a);
    }
  }
  int size = seats.Size();
  // Print back and pop back until ends
  for (auto i = 0; i < size; i++) {
    std::cout << seats.Back() <<" ";
    seats.PopBack();
  }
  std::cout << std::endl;
  return 0;
}
