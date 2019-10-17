#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include "treemap.h"

// Function for printing all donors and amount
void all(Treemap<int, std::string> &donation) {
  int min = donation.MinKey();
  for (int i = 0; i < 10; i++) {
    std::cout << donation.Get(min) << " (" << min << ")" << std::endl;
    if (min < donation.MaxKey()) {
      min = donation.CeilKey(min + 1);
    }
  }
}

// Function for finding the amount whether smaller, larger or equal
int find(Treemap<int, std::string> &donation, int amount, char choice) {
  if (choice == ' ') {
    if (donation.ContainsKey(amount)) {
    } else {
      std::cout << "No match" << std::endl;
      exit(1);
    }
  } else if (choice == '+') {
    if (donation.MaxKey() >= amount) {
      amount = donation.CeilKey(amount + 1);
    } else {
      std::cout << "No match" << std::endl;
      exit(1);
    }
  } else if (choice == '-') {
    if (donation.MinKey() <= amount) {
      amount = donation.FloorKey(amount - 1);
    } else {
      std::cout << "No match" << std::endl;
      exit(1);
    }
  }
  return amount;
}

int main(int argc, char *argv[]) {
  // Check to see if arguments are complete
  if (argv[1] && argv[2]) {
  } else {
    std::cerr << "Usage: ./eff_donations <donations_file.dat>"
    << " <command> [<args>]" << std::endl;
    return 1;
  }
  std::string input2 = argv[2];
  char input3;
  int amount;
  // Check to see if arguments are complete with "who"
  if (input2 == "who") {
    if (!argv[3]) {
      std::cerr << "Command 'who' expects another argument: [+/-]amount"
      << std::endl;
      return 1;
    }
    std::string arg3 = argv[3];
    if (arg3[0] == '+' || arg3[0] == '-') {
      input3 = arg3[0];
      arg3.erase(0, 1);
    } else {
      input3 = ' ';
    }
    amount = stoi(arg3);
  }

  // Check to see if file can be opened
  std::ifstream list(argv[1]);
  if (!list) {
    std::cerr << "Error: cannot open file " << argv[1]
    << std::endl;
    return 1;
  }

  // Declares treemap
  Treemap<int, std::string> donation;
  std::vector<std::string> values;
  std::string line;
  // reads each line using getline, then cast to isstream
  // and use getline to read in values split by comma
  while (std::getline(list, line)) {
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ',')) {
      values.push_back(token);
    }
  }
  // values into treemap
  for (unsigned int i = 0; i < values.size(); i += 2) {
    int amount = stoi(values[i + 1]);
    donation.Insert(amount, values[i]);
  }

  // Perform actions based on command line arguments
  if (input2 == "all") {
    all(donation);
  } else if (input2 == "rich") {
    int max = donation.MaxKey();
    std::cout << donation.Get(max) << " (" << max << ")" << std::endl;
  } else if (input2 == "cheap") {
    int min = donation.MinKey();
    std::cout << donation.Get(min) << " (" << min << ")" << std::endl;
  } else if (input2 == "who") {
    int result = find(donation, amount, input3);
    std::cout << donation.Get(result) << " (" << result << ")" << std::endl;
  } else {
    std::cerr << "Command" << " '" << input2 << "' " << "is invalid"
      << std::endl;
    std::cerr << "Possible commands are: all|cheap|rich|who" << std::endl;
    return 1;
  }
}

