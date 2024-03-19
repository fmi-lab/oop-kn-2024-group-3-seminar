#include <functional>
#include <iostream>

std::function<void(int)> switch_fn(int n, std::function<void(int)> f,
                                   std::function<void(int)> g) {
  return [=](int x) mutable {
    if (n > 0) {
      --n;
      return f(x);
    }
    return g(x);
  };
}

int main() {
  auto f = switch_fn(
      4, [](int x) { std::cout << x << '\n'; },
      [](int x) { std::cout << x + 5 << '\n'; });
  f(1);
  f(1);
  f(1);
  f(1);
  f(1);
  f(1);

  return 0;
}