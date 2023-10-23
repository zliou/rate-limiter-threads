#include <iostream>
#include <thread>

void PrintRange(int start, int end) {
  for (int i = start; i < end; ++i) {
    std::cout << i << std::endl;
  }
}

int main() {
  return 0;
}

