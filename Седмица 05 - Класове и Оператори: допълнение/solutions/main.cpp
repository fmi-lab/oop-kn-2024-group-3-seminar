#include <cstring>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>

class Dish {
public:
  Dish(
    const char* name = "", 
    double price = 0,
    double grams = 0,
    double calories = 0
  ) : name(new char[strlen(name) + 1]{}),
      price(price),
      grams(grams),
      calories(calories) {
    strcpy(this->name, name);
  }

  Dish(const Dish& other)
   : name(new char[strlen(other.name) + 1]{}),
     price(other.price),
     grams(other.grams),
     calories(other.calories) {
    strcpy(this->name, other.name);
  }

  ~Dish() {
    delete[] name;
  }

  Dish& operator=(const Dish& other) {
    Dish copy(other);
    swap(copy);

    return *this;
  }

  void swap(Dish& other) {
    using std::swap;
    swap(name, other.name);
    swap(price, other.price);
    swap(grams, other.grams);
    swap(calories, other.calories);
  }

  bool operator<(const Dish& other) const {
    double this_proportion = price / grams;
    double other_proportion = other.price / other.grams;

    if(this_proportion == other_proportion) {
      return calories < other.calories;
    }

    return this_proportion < other_proportion;
  }

  friend std::ostream& operator<<(
    std::ostream& os,
    const Dish& dish) {
    return os << "Name: " << dish.name << '\n'
              << "Price: " << dish.price << '\n'
              << "Quantity: " << dish.grams << '\n'
              << "Calories: " << dish.calories << '\n';
  }

  friend std::istream& operator>>(
    std::istream& is,
    Dish& dish) {
    double price, grams, calories;
    // char name[255]{};
    // is.getline(name, 255);
    char* name = new char[255]{};
    std::size_t counter = 1;

    do {
      char* newName = new char[counter * 255]{};
      strcpy(newName, name);
      char readName[255]{};
      is.getline(readName, 255);
      strcat(newName, readName);
      ++counter;
      delete [] name;
      name = newName;
    } while(is.eof());

    is >> price >> grams >> calories;

    dish = Dish(name, price, grams, calories);

    delete[] name;

    return is;
  }

private:
  char* name;
  double price, grams, calories;
};

int main() { 
  Dish dish;
  std::cin >> dish;
  std::cout << dish;
  return 0;
}