#include "student.hpp"
#include <iostream>

int main() {
  Student student("Ivan", 2, 4, 80145, 5.32);

  Student copy("Dragan", 1, 3, 80182, 3.21);

  copy = student;
  copy.info();

  Student default_student;
  default_student.info();

  return 0;
}