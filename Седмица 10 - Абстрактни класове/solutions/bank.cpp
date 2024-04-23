#include <cstddef>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

class Serializable {
  virtual void print(std::ostream& os = std::cout) const = 0;
  virtual void read(std::istream& is = std::cin) const = 0;
};

class Account: public Serializable {
public:
  Account(
    const std::string& id = "<anonymous>",
    double balance = 0,
    double interest = 0)
  : id(id),
    balance(balance),
    interest(interest) {}

  virtual ~Account() = default;

  void print(std::ostream& os = std::cout) const override {
    os << "Id: " << id << '\n' <<
          "Balance: " << balance << '\n' <<
          "Interest: " << interest << '\n';
  }

  void read(std::istream& is = std::cin) const override {
    // TODO:
  }

  virtual void deposit(double amount) {
    balance += amount;
  }

  virtual void withdraw(double amount) {
    if(balance - amount < 0) {
      std::cerr << "Insufficient balance\n";
    }

    balance -= amount;
  }

  virtual void add_interest() {
    balance *= interest;
  }

  bool operator==(const std::string& id) {
    return this->id == id;
  }

  friend std::ostream& operator<<(std::ostream& os, const Account& account) {
    account.print(os);
    return os;
  } 

  virtual Account* clone() const {
    return new Account(*this);
  }

private:
  std::string id;
  double balance, interest;
};

class CheckingAccount : public Account {
public:
  CheckingAccount(
    const std::string& id = "<anonymous>",
    double balance = 0,
    double interest = 0,
    double transaction_fee = 0)
  : Account(id, balance, interest),
    transaction_fee(transaction_fee) {}
  
  void withdraw(double amount) final {
    Account::withdraw(amount + transaction_fee);
  }

  CheckingAccount* clone() const final {
    return new CheckingAccount(*this);
  }

  void print(std::ostream& os = std::cout) const final {
    Account::print(os);
    os << "Transaction fee: " << transaction_fee << '\n';
  }

private:
  double transaction_fee;
};

class SavingsAccount : public Account {
public:
  SavingsAccount(
    const std::string& id = "<anonymous>",
    double balance = 0,
    double interest = 0,
    double withdraw_limit = 0)
  : Account(id, balance, interest),
    withdraw_limit(withdraw_limit) {}

  void withdraw(double amount) final {
    if(amount < withdraw_limit) {
      Account::withdraw(amount);
      return;
    }

    std::cerr << "You reached your limit\n";
  }

  SavingsAccount* clone() const final {
    return new SavingsAccount(*this);
  }

  void print(std::ostream& os = std::cout) const final {
    Account::print(os);
    os << "Withdraw limit: " << withdraw_limit << '\n';
  }

private:
  double withdraw_limit;
};

class SalaryAccount : public Account {
public:
  SalaryAccount(
    const std::string& id = "<anonymous>",
    double balance = 0,
    double interest = 0,
    double monthly_salary = 0)
  : Account(id, balance, interest),
    monthly_salary(monthly_salary) {}

  void add_interest() final {
    Account::add_interest();
    deposit(0.05 * monthly_salary);
  }

  SalaryAccount* clone() const final {
    return new SalaryAccount(*this);
  }

  void print(std::ostream& os = std::cout) const final {
    Account::print(os);
    os << "Monthly salary: " << monthly_salary << '\n';
  }

private:
  double monthly_salary;
};

class Bank {
public:
  Bank(std::size_t capacity = 0) 
  : capacity(capacity),
    size(0),
    data(nullptr) {}

  Bank(const Bank& other)
    : capacity(other.capacity),
      size(other.size),
      data(new Account*[other.capacity]{}) {
    for(std::size_t i = 0; i < other.size; ++i) {
      data[i] = other.data[i]->clone();
    }
  }

  Bank& operator=(const Bank& other) {
    Bank copy(other);
    swap(copy);

    return *this;
  }

  void swap(Bank& other) {
    using std::swap;

    swap(data, other.data);
    swap(size, other.size);
    swap(capacity, other.capacity);
  }

  ~Bank() { deallocate(); }

  void add(const Account& account) {
    if(size == capacity) {
      resize();
    }

    data[size++] = account.clone();
  }

  void deposit_to(const std::string& id, double amount) {
    Account* account = find(id);

    if(!account) {
      std::cerr << "Invalid account id\n";
    }

    account->deposit(amount);
  }

  void withdraw_from(const std::string& id, double amount) {
    Account* account = find(id);

    if(!account) {
      std::cerr << "Invalid account id\n";
    }

    account->withdraw(amount);
  }

  void add_interest() {
    for(std::size_t i = 0; i < size; ++i) {
      data[i]->add_interest();
    }
  }

  void print(std::ostream& os = std::cout) const {
    for(std::size_t i = 0; i < size; ++i) {
      data[i]->print(os);
    }
  }
private:
  Account** data;
  std::size_t size, capacity;

  void deallocate() {
    for(std::size_t i = 0; i < size; ++i) {
      delete data[i];
    }

    delete[] data;
  }

  void resize() {
    if(capacity == 0) {
      capacity = 1;
    } 

    Account** new_data = new Account*[capacity *= 2]{};
    for (std::size_t i = 0; i < size; ++i) {
      new_data[i] = data[i];
    }

    delete [] data;
    data = new_data;
  }

  Account* find(const std::string& id) const {
    for(std::size_t i = 0; i < size; ++i) {
      if(*data[i] == id) {
        return data[i];
      }
    }

    return nullptr;
  }
};

int main() {
  Bank bank;
  Account account("1", 100, 1.01);
  CheckingAccount checking_account("2", 80, 1.03, 5);
  SavingsAccount savings_account("3", 120, 1.001, 100);
  SalaryAccount salary_account("4", 110, 1.02, 700);

  bank.add(account);
  bank.add(checking_account);
  bank.add(savings_account);
  bank.add(salary_account);

  bank.print();
  return 0;
}