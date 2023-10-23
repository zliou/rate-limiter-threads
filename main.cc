#include <iostream>
#include <thread>
#include <vector>


void PrintRange(int thread_number, int start, int end) {
  for (int i = start; i < end; ++i) {
    std::cout << "Thread " << thread_number << ": " << i << std::endl;
  }
}

int main() {
  int num_threads = 20;
  std::vector<std::thread> threads(num_threads);

  // Initialize threads.
  for (size_t i = 0; i < num_threads; ++i) {
    threads[i] = std::thread(PrintRange, i, 0, 9);
  }

  // Join threads.
  for (std::thread& t : threads) {
    t.join();
  }

  return 0;
}

