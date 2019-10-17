#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  std::ifstream ifs(argv[1]);
  std::string store;
  while (true) {
    char x;
    ifs >> x;
    if (ifs.eof()) {
      break;
    }
    store.push_back(x);
  }
  cout << store.size();
  return 0;
}
