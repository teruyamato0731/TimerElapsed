#ifndef TIMER_ELAPSED_H_
#define TIMER_ELAPSED_H_

namespace rct {

template<class T>
struct ElapsedTime {
  template<class F>
  auto& then(F&& f) & {
    if(is_elapsed) f();
    return *this;
  }
  template<class F>
  auto then(F&& f) && {
    if(is_elapsed) f();
    return std::move(*this);
  }
  template<class F>
  auto& or_else(F&& f) & {
    if(!is_elapsed) f();
    return *this;
  }
  template<class F>
  auto or_else(F&& f) && {
    if(!is_elapsed) f();
    return std::move(*this);
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
    if(delta > wait) {
      pre_ = now;
      return ElapsedTime<unit_time>{delta, true};
    } else {
      return ElapsedTime<unit_time>{delta, false};
    }
  }
  time_point pre_;
};

}  // namespace rct

#endif  // TIMER_ELAPSED_H_
