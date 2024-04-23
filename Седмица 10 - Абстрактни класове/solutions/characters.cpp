#include <cstddef>
#include <cstring>
#include <iostream>

class Character {
public:
  Character(const char *name = "<anonymous>", double damage = 0,
            double hp = 100)
      : name(new char[strlen(name) + 1]{}), damage(damage), hp(hp) {
    strcpy(this->name, name);
  }

  Character(const Character &other)
      : name(new char[strlen(other.name) + 1]{}), damage(other.damage),
        hp(other.hp) {
    strcpy(name, other.name);
  }

  virtual ~Character() { delete[] name; }

  Character &operator=(const Character &other) {
    Character copy(other);
    swap(copy);

    return *this;
  }

  void swap(Character &other) {
    using std::swap;

    swap(name, other.name);
    swap(damage, other.damage);
    swap(hp, other.hp);
  }

  bool is_alive() const { return hp != 0; }

  virtual void take_damage(double points) { hp = std::max(hp - points, 0.0); }

  virtual void deal_damage_to(Character &other) const {
    other.take_damage(damage);
  }

  virtual void heal(double points) { hp += points; }

  bool compare_name(const char *name) const {
    return strcmp(this->name, name) == 0;
  }

  bool operator==(const Character &other) const {
    return compare_name(other.name);
  }

  void print() const {
    std::cout << "Name: " << name << '\n';
    type();
    std::cout << "HP: " << hp << '\n' << "DMG: " << damage << '\n';
  }

  virtual Character* clone() const {
    return new Character(*this);
  }

private:
  char *name;
  double damage, hp;

  virtual void type() const { std::cout << "Type: Ordinary Character\n"; }
};

class Knight : public Character {
public:
  Knight(const char *name = "<anonymous_knight>", double damage = 0,
         double hp = 120)
      : Character(name, damage, hp) {}

  void take_damage(double points) final {
    Character::take_damage(points * 3 / 4);
  }

  void heal(double points) final { Character::heal(points * 1.05); }

  Knight* clone() const final {
    return new Knight(*this);
  }

private:
  void type() const final { std::cout << "Type: Knight\n"; }
};

class Archer : public Character {
public:
  Archer(const char *name = "<anonymous_knight>", double damage = 0,
         double hp = 80)
      : Character(name, damage * 1.33, hp) {}

  void take_damage(double points) final {
    Character::take_damage(points * 1.15);
  }

  void deal_damage_to(Character &other) const final {
    Character::deal_damage_to(other);
  }

  Archer* clone() const final {
    return new Archer(*this);
  }

private:
  void type() const final { std::cout << "Type: Archer\n"; }
};

class Game {
public:
  Game() : data(nullptr), size(0), capacity(0) {}
  Game(const Game &other)
      : data(new Character *[other.capacity] {}), size(other.size),
        capacity(other.capacity) {
    for (std::size_t i = 0; i < other.size; ++i) {
      data[i] = other.data[i]->clone();
    }
  }

  ~Game() { deallocate(); }

  Game &operator=(const Game &other) {
    Game copy(other);
    swap(copy);

    return *this;
  }

  void swap(Game &other) {
    using std::swap;

    swap(data, other.data);
    swap(size, other.size);
    swap(capacity, other.capacity);
  }

  void add(const Character &character) {
    if (size == capacity) {
      resize();
    }

    data[size++] = character.clone();
  }

  void battle(const char *attacker, const char *target) {
    Character *attacking_character = find(attacker);

    if (!attacking_character) {
      std::cout << "Cannot find attacker\n";
      return;
    }

    Character *targeted_character = find(target);

    if (!targeted_character) {
      std::cout << "Cannot find target\n";
      return;
    }

    attacking_character->deal_damage_to(*targeted_character);

    if(!targeted_character->is_alive()) {
      std::cout << "Target was eliminated\n";
      remove(target);
    }
  }

  void heal(double amount) {
    for(std::size_t i = 0; i < size; ++i) {
      data[i]->heal(amount);
    }
  }

  void print() const {
    for(std::size_t i = 0; i < size; ++i) {
      data[i]->print();
      std::cout << '\n';
    }
  }

private:
  Character **data;
  std::size_t size, capacity;

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    Character **new_data = new Character *[capacity *= 2] {};
    for (std::size_t i = 0; i < size; ++i) {
      new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;
  }

  Character *find(const char *name) const {
    for (std::size_t i = 0; i < size; ++i) {
      if (data[i]->compare_name(name)) {
        return data[i];
      }
    }

    return nullptr;
  }

  void remove(const char* name) {
    std::size_t index = 0;
    while(index < size && !data[index]->compare_name(name)) {
      ++index;
    }

    delete data[index];

    for(std::size_t i = index; i < size - 1; ++i) {
      std::swap(data[i], data[i+1]);
    }

    --size;
  }

  void deallocate() {
    for(std::size_t i = 0; i < size; ++i) {
      delete data[i];
    }

    delete [] data;
  }
};

int main() {
  Game game;
  Knight* knight = new Knight("Arthur", 20, 120);
  Archer* archer = new Archer("Legolas", 40, 80);
  Character* character = new Character("Maugli", 5, 70);

  game.add(*knight);
  game.add(*archer);
  game.add(*character);

  game.battle("Shrek", "Arthur");
  game.battle("Legolas", "Maugli");
  game.battle("Arthur", "Maugli");
  game.print();

  game.heal(20);
  game.print();

  delete knight;
  delete archer;
  delete character;
  return 0;
}