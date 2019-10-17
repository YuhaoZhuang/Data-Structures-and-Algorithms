#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono> // NOLINT (build/c++11)

// class to calculate time needed for each search methods
class Time {
 public:
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point end;
  void start_now() {
    start = std::chrono::high_resolution_clock::now();
  }
  void end_now() {
    end = std::chrono::high_resolution_clock::now();
  }
};

// class for containnig the coordinates and areas of the rectangles
class Rectangle {
 public:
  int x1, y1, x2, y2, area;
  Rectangle(int x1, int y1, int x2, int y2, int area):
    x1(x1), y1(y1), x2(x2), y2(y2), area(area) {}
  // overload the < operator to utilize the sort() function
  bool operator< (const Rectangle& next) {
    return area < next.area;
  }
};

int main(int argc, char *argv[]) {
  // check to see if the number of required arguments are complete
  if (argv[1] && argv[2] && argv[3]) {
  } else {
    std::cerr << "Usage: ./rectangle_search <rectangle_file.dat> <"
      <<"area_file.dat> <result_file.dat>" <<std::endl;
    return 1;
  }
  // read in first argument and check, check if valid, then put the
  // coordinates into a vector of Rectangle Class
  std::ifstream rectangle(argv[1]);
  std::vector<Rectangle> rectangle_class;
  if (rectangle) {
    while (!rectangle.eof()) {
      int a, b, c, d;
      rectangle >> a;
      rectangle >> b;
      rectangle >> c;
      rectangle >> d;
      int surface_area = (c - a)*(d - b);
      rectangle_class.push_back(Rectangle(a, b, c, d, surface_area));
    }
  } else {
    std::cerr << "Error: cannot open file " << argv[1] << std::endl;
    return 1;
  }
  // read in second argument and check to see if it is valid, then put the
  // areas into a vector
  std::ifstream area(argv[2]);
  std::vector<int> area_save;
  if (area) {
    while (!area.eof()) {
      int x;
      area >> x;
      area_save.push_back(x);
    }
  } else {
    std::cerr << "Error: cannot open file " << argv[2] << std::endl;
    return 1;
  }
  // ask for either linear or bineary search and ask again of input is not valid
  char choice;
  std::cout << "Choice of search method ([l]inear, [b]inary)?" <<std::endl;
  std::cin >> choice;
  while (choice != 'l' && choice != 'b') {
    std::cerr<< "Incorrect choice" << std::endl;
    std::cin >> choice;
  }
  // do linear or binary search depending on user input
  int count = 0;
  Time time;  // initalize Time class
  if (choice == 'l') {  // linear search
    time.start_now();  // get current time
    // run thrugh vector of areas and then search for matched ones
    // through vector of rectangles classes, break inner loop if found
    for (unsigned int i = 0; i < area_save.size(); i++) {
      for (unsigned int j = 0; j < rectangle_class.size(); j++) {
        if (rectangle_class[j].area == area_save[i]) {
          count += 1;
          break;
        }
      }
    }
    time.end_now();  // get current time
    double passed = std::chrono::duration<double,
      std::micro>(time.end - time.start).count();  // get time it takes to sort
    std::cout << "CPU time: " << passed << " microseconds" << std::endl;
  } else if (choice == 'b') {  // binary search
    time.start_now();
    // sort the rectangle objects in vecotr by their surface area
    sort(rectangle_class.begin(), rectangle_class.end());
    // run through vector of areas, and then divide the rectangle class
    // into half each time to do binary search, break inner loop if found
    for (unsigned int i = 0; i < area_save.size(); i++) {
      int low = 0;
      int high = rectangle_class.size() - 1;
      while (low <= high) {
        int mid = low + (high - low) / 2;
        if (rectangle_class[mid].area == area_save[i]) {
          count += 1;
          break;
        } else if (rectangle_class[mid].area < area_save[i]) {
          low = mid + 1;
        } else if (rectangle_class[mid].area > area_save[i]) {
          high = mid - 1;
        }
      }
    }
    time.end_now();
    double passed = std::chrono::duration<double,
      std::micro>(time.end - time.start).count();
    std::cout << "CPU time: " << passed << " microseconds" << std::endl;
  }
  // take 3rd input, see if valid, and print number of areas found to it
  std::ofstream output(argv[3]);
  if (output) {
  } else {
    std::cerr << "Error: cannot open file " << argv[3] << std::endl;
    return 1;
  }
  output << count << std::endl;
  output.close();
  return 0;
}
