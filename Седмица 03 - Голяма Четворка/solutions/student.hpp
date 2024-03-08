#ifndef HPP_STUDENT
#define HPP_STUDENT

class Student {
public:
  Student(const char *name = "<Anonymous>", int year = 1, int group = 1,
          int fn = 0, double average_grade = 2);
  Student(const Student &);
  ~Student();
  Student &operator=(const Student &);

  void info() const;
  bool can_graduate() const;
  void swap(Student &);

private:
  char *name;
  int year, group, fn;
  double average_grade;

  int set_year(int) const;
  double set_average_grade(double) const;
};

#endif