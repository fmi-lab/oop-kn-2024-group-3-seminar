#ifndef CAR_HPP
#define CAR_HPP

#include <cstddef>
#include <cstring>

class Car {
public:
  Car(const char* brand = "", const char* model = "", double average_speed = 0);
  Car(const Car&);
  Car& operator=(const Car&);
  ~Car();

  void swap(Car&);

  double drive(double distance);

  const char* get_brand() const { return brand; };
  const char* get_model() const { return model; };
  double get_average_speed() const { return average_speed; };
  double get_distance() const { return distance; };
  std::size_t get_id() const { return id; }

private:
  static std::size_t objects_count;

  char* brand, *model;
  std::size_t id;
  double original_average_speed, average_speed, distance;
};

#endif