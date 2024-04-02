#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../libs/doctest.h"

int factorial(int n) {
  int product = 1;

  for(std::size_t i = 1; i <= n; ++i) {
    product *= i;
  }

  return product;
}

TEST_CASE("factorial returns correct values") {
  SUBCASE("factorial(0) should return 1") {
    int result = factorial(0);

    CHECK_EQ(result, 1);
  }

  SUBCASE("factorial(n) should return n! for n >= 0") {
    int result = factorial(5);

    CHECK_EQ(result, 120);
  }

  SUBCASE("factorial(n) should throw std::invalid_argument exception for n < 0") {
    CHECK_THROWS_AS(factorial(-2), std::invalid_argument);
  }
}