#include <cstring>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../libs/doctest.h"
#include "car.hpp"

TEST_CASE("id increments with every new car") {
  Car mazda("mazda", "rx-7 fd3s", 55.5);
  Car nissan("nissan", "skyline gt-r 34", 64.2);

  REQUIRE_EQ(mazda.get_id(), 0);
  CHECK_EQ(nissan.get_id(), 1);
}

TEST_CASE("Car constructor") {
  SUBCASE("with arguments creates valid car") {
    Car car("mazda", "rx-7 fd3s", 55.5);

    CHECK_EQ(strcmp(car.get_brand(), "mazda"), 0);
    CHECK_EQ(strcmp(car.get_model(), "rx-7 fd3s"), 0);
    CHECK_EQ(car.get_average_speed(), doctest::Approx(55.5));
    CHECK_EQ(car.get_distance(), 0);
  }

  SUBCASE("without argument creates valid car") {
    Car car;

    CHECK_EQ(strcmp(car.get_brand(), ""), 0);
    CHECK_EQ(strcmp(car.get_model(), ""), 0);
    CHECK_EQ(car.get_average_speed(), doctest::Approx(0));
    CHECK_EQ(car.get_distance(), 0);
  }
}

TEST_CASE("Car copy constructor") {
  Car car("nissan", "skyline gt-r 34", 64.2);

  SUBCASE("copies another car correctly") {
    Car copy(car);

    CHECK_EQ(strcmp(copy.get_brand(), "nissan"), 0);
    CHECK_EQ(strcmp(copy.get_model(), "skyline gt-r 34"), 0);
    CHECK_EQ(copy.get_average_speed(), doctest::Approx(64.2));
    CHECK_EQ(copy.get_distance(), 0);
  }

  SUBCASE("makes deep copy of the provided car") {
    Car *copy = new Car(car);
    delete copy;

    CHECK_EQ(strcmp(car.get_brand(), "nissan"), 0);
    CHECK_EQ(strcmp(car.get_model(), "skyline gt-r 34"), 0);
    CHECK_EQ(car.get_average_speed(), doctest::Approx(64.2));
    CHECK_EQ(car.get_distance(), 0);
  }
}

TEST_CASE("Car copy asignment operator") {
  Car car("nissan", "skyline gt-r 34", 64.2);

  SUBCASE("copies another car correctly") {
    Car copy;
    copy = car;

    CHECK_EQ(strcmp(copy.get_brand(), "nissan"), 0);
    CHECK_EQ(strcmp(copy.get_model(), "skyline gt-r 34"), 0);
    CHECK_EQ(copy.get_average_speed(), doctest::Approx(64.2));
    CHECK_EQ(copy.get_distance(), 0);
  }

  SUBCASE("makes deep copy of the provided car") {
    Car *copy = new Car;
    *copy = car;
    delete copy;

    CHECK_EQ(strcmp(car.get_brand(), "nissan"), 0);
    CHECK_EQ(strcmp(car.get_model(), "skyline gt-r 34"), 0);
    CHECK_EQ(car.get_average_speed(), doctest::Approx(64.2));
    CHECK_EQ(car.get_distance(), 0);
  }
}

TEST_CASE("drive method") {
  Car car("toyota", "supra mk4", 100);

  SUBCASE("calculates time correctly when didn't travel for more than 100km") {
    CHECK_EQ(car.drive(75), doctest::Approx(0.75));
  }

  SUBCASE("increments car's travelled distance") {
    car.drive(60);

    CHECK_EQ(car.get_distance(), doctest::Approx(60));
  }

  SUBCASE("decrements average speed when travelling for more than 100km") {
    car.drive(120);

    CHECK_EQ(car.get_average_speed(), doctest::Approx(99));
  }

  SUBCASE("calculates time correctly when travelling for more than 100km") {
    car.drive(100);

    REQUIRE_EQ(car.get_distance(), doctest::Approx(100));
    REQUIRE_EQ(car.get_average_speed(), doctest::Approx(99));

    double time = car.drive(99);

    CHECK_EQ(car.get_distance(), doctest::Approx(199));
    CHECK_EQ(car.get_average_speed(), doctest::Approx(99));
    CHECK_EQ(time, doctest::Approx(1));
  }

  SUBCASE("calculates time correctly when travelling in multiple of 100km") {
    // TODO: homework
  }
}