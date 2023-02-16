#include <chrono>
#include <iostream>

template<class T>
struct ElapsedTime {
  template<class F>
  auto then(F&& f) {
    if(is_elapsed) f();
    return *this;
  }
  template<class F>
  auto or_else(F&& f) {
    if(!is_elapsed) f();
    return *this;
  }
  const T delta;
  const bool is_elapsed;
};

template<class T>
struct TimerElapsed {
  using time_point = decltype(std::chrono::steady_clock::now());
  using unit_time = time_point::duration;
  auto operator()(const unit_time& wait) -> ElapsedTime<unit_time> {
    auto now = std::chrono::steady_clock::now();
    auto delta = now - pre_;
    std::cout << "delta\t" << delta.count() << std::endl << "wait\t" << wait.count() << std::endl;
    if(delta > wait) {
      pre_ = now;
      return ElapsedTime<unit_time>{delta, true};
    } else {
      return ElapsedTime<unit_time>{delta, false};
    }
  }
  time_point pre_;
};

int main() {
  std::cout << "hoge" << std::endl;

  using namespace std::literals::chrono_literals;
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
