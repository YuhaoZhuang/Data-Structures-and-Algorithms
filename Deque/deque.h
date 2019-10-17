#ifndef DEQUE_H_
#define DEQUE_H_

#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <utility>

template<typename T>
class Deque {
 public:
  //
  // @@@ The class's public API below should _not_ be modified @@@
  //

  // Constructor
  Deque();
  // Destructor
  ~Deque();


  //
  // Capacity
  //

  // Return true if empty, false otherwise
  // Complexity: O(1)
  bool Empty() const noexcept;
  // Return number of items in deque
  // Complexity: O(1)
  size_t Size() const noexcept;
  // Resize internal data structure to fit precisely the number of items and
  // free unused memory
  // Complexity: O(N)
  void ShrinkToFit();


  //
  // Element access
  //

  // Return item at pos @pos
  // Complexity: O(1)
  T& operator[](size_t pos);
  // Return item at front of deque
  // Complexity: O(1)
  T& Front();
  // Return item at back of deque
  // Complexity: O(1)
  T& Back();


  //
  // Modifiers
  //

  // Clear contents of deque (make it empty)
  // Complexity: O(1)
  void Clear(void) noexcept;
  // Push item @value at front of deque
  // Complexity: O(1) amortized
  void PushFront(const T &value);
  // Push item @value at back of deque
  // Complexity: O(1) amortized
  void PushBack(const T &value);
  // Remove item at front of deque
  // Complexity: O(1) amortized
  void PopFront();
  // Remove item at back of deque
  void PopBack();
  // Complexity: O(1) amortized

 private:
    std::unique_ptr<T[]> array;
    int size, array_size, front, tail;
    bool check_full();
    void resize(int position);
};

template <typename T>
Deque<T>::Deque() : array(std::unique_ptr<T[]>(new T[3])),
size(0), array_size(3), front(-1), tail(0) {}

template <typename T>
Deque<T>::~Deque() = default;

template<typename T>
bool Deque<T>::Empty() const noexcept {
  if (size == 0) {
    return true;
  } else {
    return false;
  }
}

template<typename T>
size_t Deque<T>::Size() const noexcept {
  return size;
}

// Shrink array of the more than 75% of array is not
// being used, shrink size by half
template<typename T>
void Deque<T>::ShrinkToFit() {
  if (array_size/4 > size) {
    std::unique_ptr <T[]> new_array(new T[array_size/2]);
    int temp_front = front;
    for (auto i = 0; i < size; i++) {
      if (temp_front >= array_size) {
        temp_front = 0;
      }
      new_array[i] = array[temp_front];
      temp_front++;
    }
    front = 0;
    tail = size - 1;
    array_size /= 2;
    array = std::move(new_array);
  }
}

template<typename T>
T& Deque<T>::operator[](size_t pos) {
  int a = static_cast<int>(pos);
  if (a >= 0 && a < size) {
    if (front + a < array_size) {
      return array[front + pos];
    } else {
      int rest = front + pos - array_size;
      return array[rest];
    }
  } else {
    throw std::out_of_range("Incorrect Index");
  }
}

template <typename T>
T& Deque<T>::Front() {
  if (size > 0) {
    return array[front];
  } else {
    throw std::out_of_range("No front available");
  }
}

template <typename T>
T& Deque<T>::Back() {
  if (size > 0) {
    return array[tail];
  } else {
    throw std::out_of_range("No back available");
  }
}

template <typename T>
void Deque<T>::Clear(void) noexcept {
  std::unique_ptr <T[]> new_array(new T[3]);
  array_size = 3;
  size = 0;
  front = -1;
  tail = 0;
}

template <typename T>
bool Deque<T>::check_full() {
  if (size == array_size) {
    return true;
  } else {
    return false;
  }
}

// Increase the size of array by 2 and copy everthing from original
template <typename T>
void Deque<T>::resize(int position) {
  int count = 0;
  std::unique_ptr <T[]> new_array(new T[array_size*2]);
  for (auto i = 0; i < array_size; i++) {
    if (position == i) {
      count = i + size;
    }
    new_array[count] = array[i];
    count++;
  }
  array = std::move(new_array);
  array_size *= 2;
}

template <typename T>
void Deque<T>::PushFront(const T &value) {
  if (Empty()) {
    front = 0;
    tail = 0;
    std::unique_ptr <T[]> new_array(new T[3]);
    array = std::move(new_array);
    array_size = 3;
  } else if (front == 0) {
    front = array_size - 1;
    if (check_full()) {
      resize(array_size);
      front = array_size - 1;
    }
  } else {
    front = front - 1;
    if (check_full()) {
      front += 1;
      resize(front);
      front += size - 1;
    }
  }
  size += 1;
  array[front] = value;
}

template <typename T>
void Deque<T>::PushBack(const T &value) {
  if (Empty()) {
    front = 0;
    tail = 0;
    std::unique_ptr <T[]> new_array(new T[3]);
    array = std::move(new_array);
    array_size = 3;
  } else if ( tail == size -1 ) {
    tail++;
    if (check_full()) {
      resize(tail);
    }
  } else if (tail == array_size - 1) {
    if (front != 0) {
      tail = 0;
    } else {
      tail++;
      resize(tail);
    }
  } else {
    tail++;
    if (check_full()) {
      resize(front);
      front += size;
    }
  }
  size += 1;
  array[tail] = value;
}

template <typename T>
void Deque<T>::PopFront() {
  if (Empty()) {
    throw std::out_of_range("Deque has no values");
  } else if (size == 1) {
    front = -1;
    tail = -1;
    size -= 1;
  } else if (front == array_size - 1) {
    front = 0;
    size -= 1;
  } else {
    front += 1;
    size -= 1;
  }
}

template <typename T>
void Deque<T>::PopBack() {
  if (Empty()) {
    throw std::out_of_range("Deque has no values");
  } else if (size == 1) {
    front = -1;
    tail = -1;
    size -= 1;
  } else if (tail== 0) {
    tail = array_size - 1;
    size -= 1;
  } else {
    tail -= 1;
    size -= 1;
  }
}



#endif  // DEQUE_H_
