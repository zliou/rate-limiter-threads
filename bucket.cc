#include <chrono>
#include <deque>
#include <iostream>
#include <stack>
#include <string>
#include <thread>


void TakeToken(std::string thread_name, std::stack<int>* tokens, int rate_ms) {
  while (true) {
    if (tokens->size() > 0) {
      int token = tokens->top();
      tokens->pop();
      std::cout << "  Thread " << thread_name << " took token #" << token << std::endl;
    } else {
      std::cout << "  --  Thread " << thread_name << " could not take a token." << std::endl;
    }
    
    // Attempt to take a new token every `rate_ms` milliseconds.
    std::this_thread::sleep_for(std::chrono::milliseconds(rate_ms));
  }
}

void PlaceToken(std::stack<int>* tokens, int rate_ms, size_t max_tokens = 5) {
  while (true) {
    if (tokens->size() < max_tokens) {
      int token_number = tokens->size();
      tokens->push(token_number);
      std::cout << "Placed token #" << token_number << std::endl;
    } else {
      std::cout << "No tokens were placed because the bucket is full." << std::endl;
    }

    // Attempt to place a new token every `rate_ms` milliseconds.
    std::this_thread::sleep_for(std::chrono::milliseconds(rate_ms));
  }
}

void RunExperiment() {
  std::deque<int> init = {0,1,2,3,4,5};
  std::stack<int> bucket(init);  // Start with a full bucket of tokens.
  std::thread refiller(PlaceToken, &bucket, /*rate_ms=*/180, /*max_tokens*/5);
  std::thread consumer1(TakeToken, "A", &bucket, /*rate_ms=*/225);
  std::thread consumer2(TakeToken, "B", &bucket, /*rate_ms=*/800);
  std::thread consumer3(TakeToken, "C", &bucket, /*rate_ms=*/770);
  std::thread consumer4(TakeToken, "D", &bucket, /*rate_ms=*/999);

  consumer1.join();
  consumer2.join();
  consumer3.join();
  consumer4.join();
}


int main() {
  RunExperiment();
  return 0;
}

