#include "student.hpp"
#include <cstring>
#include <iostream>

Student::Student(const char *name, int year, int group, int fn,
                 double average_grade)
    : name(new char[strlen(name) + 1]{}), year(set_year(year)), group(group),
      fn(fn), average_grade(set_average_grade(average_grade)) {
  strcpy(this->name, name);
}

Student::Student(const Student &other)
    : name(new char[strlen(other.name) + 1]{}), year(set_year(other.year)),
      group(other.group), fn(other.fn),
      average_grade(set_average_grade(other.average_grade)) {
  strcpy(name, other.name);
}

Student::~Student() { delete[] name; }

Student &Student::operator=(const Student &other) {
  // if (this != &other) {
  //   delete[] name;
  //   name = new char[strlen(other.name) + 1]{};
  //   strcpy(name, other.name);
  //   year = other.year;
  //   group = other.group;
  //   fn = other.fn;
  //   average_grade = other.average_grade;
  // }

  Student copy(other);
  swap(copy);

  return *this;
}

bool Student::can_graduate() const { return average_grade >= 3; }

void Student::swap(Student &other) {
  using std::swap;

  swap(name, other.name);
  swap(year, other.year);
  swap(group, other.group);
  swap(fn, other.fn);
  swap(average_grade, other.average_grade);
}

void Student::info() const {
  std::cout << "Name: " << name << '\n'
            << "Year: " << year << '\n'
            << "Group: " << group << '\n'
            << "Faculty number: " << fn << '\n'
            << "Average grade: " << average_grade << '\n';
}

int Student::set_year(int year) const {
  if (year < 1 || year > 4) {
    return 1;
  }
  return year;
}

double Student::set_average_grade(double average_grade) const {
  if (average_grade < 2 || average_grade > 6) {
    return 2;
  }
  return average_grade;
}