#include <cstddef>
#include <cstring>
#include <iostream>

class Animal {
public:
  Animal(const char *name, unsigned age, double weight)
      : name(new char[strlen(name) + 1]{}), age(age), weight(weight) {
    strcpy(this->name, name);
  }

  Animal(const Animal &other)
      : name(new char[strlen(other.name) + 1]{}), age(other.age),
        weight(other.weight) {
    strcpy(name, other.name);
  }

  Animal &operator=(const Animal &other) {
    Animal copy(other);
    swap(copy);

    return *this;
  }

  void swap(Animal &other) {
    using std::swap;

    swap(name, other.name);
    swap(age, other.age);
    swap(weight, other.weight);
  }

  ~Animal() { delete[] name; }

  void print() const {
    std::cout << "Name: " << name << '\n'
              << "Age: " << age << '\n'
              << "Weight: " << weight << '\n';
  }

private:
  char *name;
  unsigned age;
  double weight;

  // protected:
  //   bool has_legs;
};

class Feline : public Animal {
public:
  Feline(const char *name, unsigned age, double weight, unsigned lives)
      : Animal(name, age, weight), lives(lives) {}

  void print() const {
    Animal::print();
    std::cout << "Remaining lives: " << lives << '\n';
  }

  void swap(Feline &other) {
    using std::swap;

    Animal::swap(other);
    swap(lives, other.lives);
  }

private:
  unsigned lives;
};

class Cat : public Feline {
public:
  Cat(const char *name, unsigned age, double weight, unsigned lives,
      const char *owner)
      : Feline(name, age, weight, lives), owner(new char[strlen(owner) + 1]{}) {
    strcpy(this->owner, owner);
  }

  Cat(const Cat &other)
      : Feline(other), owner(new char[strlen(other.owner) + 1]{}) {
    strcpy(owner, other.owner);
  }

  ~Cat() { delete[] owner; }

  Cat &operator=(const Cat &other) {
    Cat copy(other);
    swap(copy);

    return *this;
  }

  void swap(Cat &other) {
    using std::swap;

    Feline::swap(other);
    swap(owner, other.owner);
  }

  void print() const {
    Feline::print();
    std::cout << "Owner: " << owner << '\n';
  }

private:
  char *owner;
};

class Person {
public:
  Person(const char *name = "", unsigned age = 0, const char *mail = "");
  Person(const Person &other);
  ~Person();
  Person &operator=(const Person &other);
  void swap(Person &other);

  void print() const;
  void send_mail(const char *message) const;
  void view_inbox() const;

private:
  char *name;
  unsigned age;
  char *mail;
};

class Student : public Person {
public:
  Student(const char *name = "", unsigned age = 0, const char *mail = "",
          unsigned faculty_number = 0);
  void swap(Student &other);
  void print() const;
  void send_mail(const char *message) const;

private:
  unsigned faculty_number;
};

class Lecturer : public Person {
public:
  Lecturer(const char *name = "", unsigned age = 0, const char *mail = "",
           unsigned faculty_number = 0, const char *department = "");
  Lecturer(const Lecturer &other);
  ~Lecturer();
  Lecturer &operator=(const Lecturer &other);

  void swap(Lecturer &other);
  void print() const;
  void send_mail(const char *message) const;

private:
  char *department;
};

class University {
public:
  University();
  University(const University& other);
  ~University();
  University& operator=(const University& other);
  void swap(University& other);

  void add_student(const Student& student);
  void add_lecturer(const Lecturer& lectur);

  // TODO: ...

private:
  // TODO: extract to separate classes
  char* name;
  Student* students;
  std::size_t students_size, students_capacity;
  Lecturer* lecturers;
  std::size_t lecturers_size, lecturers_capacity;
};

int main() {
  Animal animal("Dog", 4, 35);
  animal.print();
  std::cout << '\n';
  Feline feline("Lion", 12, 85, 1);
  feline.print();

  std::cout << '\n';
  Animal copy = static_cast<Animal>(feline);
  copy.print();

  // Feline copy2 = static_cast<Feline>(animal); -> forbidden

  Cat cat("Rumen", 7, 12, 9, "Ivancho");
  cat.print();

  std::cout << '\n';
  Cat copy_cat(cat);
  copy_cat.print();

  std::cout << '\n';
  copy_cat = Cat("Pumba", 21, 120, 1, "Timon");
  copy_cat.print();

  std::cout << '\n';
  Feline copy_feline("Pesho", 4, 24.5, 3);
  copy_feline.print();

  std::cout << '\n';
  copy_feline = feline;
  copy_feline.print();

  return 0;
}