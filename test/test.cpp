#include <TimerElapsed.h>

#include <chrono>
#include <iostream>

using namespace std::literals::chrono_literals;
using namespace rct;

int main() {
  TimerElapsed<std::chrono::steady_clock> elapsed = {std::chrono::steady_clock::now()};
  elapsed(1ms).then([] {
    std::cout << "then 1" << std::endl;
  }).or_else([] {
    std::cout << "else 1" << std::endl;
  });

  elapsed(1ns).then([] {
    std::cout << "then 2" << std::endl;
  }).or_else([] {
    std::cout << "else 2" << std::endl;
  });
}
