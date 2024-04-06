#include <algorithm>
#include <cmath>
#include "car.hpp"

std::size_t Car::objects_count = 0;

Car::Car(const char *brand, const char *model, double average_speed)
    : brand(new char[strlen(brand) + 1]{}),
      model(new char[strlen(model) + 1]{}),
      original_average_speed(average_speed), average_speed(average_speed),
      distance(0), id(objects_count++) {
  strcpy(this->brand, brand);
  strcpy(this->model, model);
}

Car::Car(const Car &other)
    : brand(new char[strlen(other.brand) + 1]{}),
      model(new char[strlen(other.model) + 1]{}),
      original_average_speed(other.original_average_speed),
      average_speed(other.average_speed), distance(other.distance),
      id(objects_count++) {
  strcpy(brand, other.brand);
  strcpy(model, other.model);
}

Car &Car::operator=(const Car &other) {
  Car copy(other);
  swap(copy);

  return *this;
}

Car::~Car() {
  delete[] brand;
  delete[] model;
}

void Car::swap(Car &other) {
  using std::swap;

  swap(brand, other.brand);
  swap(model, other.model);
  swap(original_average_speed, other.original_average_speed);
  swap(average_speed, other.average_speed);
  swap(distance, other.distance);
  swap(id, other.id);
}

double Car::drive(double distance) {
  double time = 0,
         distance_to_hundred = std::min(
             distance, std::ceil(this->distance / 100) * 100 - this->distance),
         distance_left = distance - distance_to_hundred;
  int decreases_count = std::floor(distance_left) / 100;

  time += distance_to_hundred / average_speed;

  if (distance_to_hundred > 0 &&
      (average_speed - 1) >= original_average_speed / 2) {
    average_speed -= 1;
  }

  for (std::size_t i = 0; i < decreases_count; ++i) {
    time += 100 / average_speed;
    distance_left -= 100;

    if ((average_speed - 1) >= original_average_speed / 2) {
      average_speed -= 1;
    }
  }

  time += distance_left / average_speed;

  this->distance += distance;

  return time;
}