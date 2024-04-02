#include "car.hpp"

#include <algorithm>

std::size_t Car::objects_count = 0;

Car::Car(const char* brand, const char* model, double average_speed)
  : brand(new char[strlen(brand) + 1]{}),
    model(new char[strlen(model) + 1]{}),
    original_average_speed(average_speed),
    average_speed(average_speed),
    distance(0),
    id(objects_count++) {
  strcpy(this->brand, brand);
  strcpy(this->model, model);
}

Car::Car(const Car& other)
  : brand(new char[strlen(other.brand) + 1]{}),
    model(new char[strlen(other.model) + 1]{}),
    original_average_speed(other.original_average_speed),
    average_speed(other.average_speed),
    distance(other.distance),
    id(objects_count++) {
  strcpy(brand, other.brand);
  strcpy(model, other.model);
}

Car& Car::operator=(const Car& other) {
  Car copy(other);
  swap(copy);

  return *this;
}

Car::~Car() {
  delete [] brand;
  delete [] model;
}

void Car::swap(Car& other) {
  using std::swap;

  swap(brand, other.brand);
  swap(model, other.model);
  swap(original_average_speed, other.original_average_speed);
  swap(average_speed, other.average_speed);
  swap(distance, other.distance);
  swap(id, other.id);
}

double Car::drive(double distance) {
  if(distance >= 100) {
    average_speed--;
  } 

  this->distance += distance;
  return distance / average_speed;
}