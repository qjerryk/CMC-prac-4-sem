//
// Created by qjerryk on 3/14/23.
//
#include <iostream>
#include <string>

class event {
 protected:
  int year, month, day;
  const char *name;
 public:
  event(const char *name = nullptr, int year = 0, int month = 0, int day = 0): year(year), month(month), day(day), name(name) {}
  virtual void print_res() = 0;
  virtual void change_date(int new_year, int new_month, int new_day) {
    year = new_year;
    month = new_month;
    day = new_day;
  }
  virtual void change_grade(int grade) = 0;
  //~event() {}
};

class test: public event {
 private:
  bool grade;
 public:
  test(const char *name = nullptr, int year = 0, int month = 0, int day = 0, bool grade = false): event(name, year, month, day), grade(grade) {}
  void print_res() {
    std::cout << name << " " << year << " " << month << " " << day  << " "<< (grade? "true" : "false") << std::endl;
  }
  void change_grade(int grade) {
    this->grade = grade;
  }
};

class exam: public event {
 private:
  int grade;
 public:
  exam(const char *name = nullptr, int year = 0, int month = 0, int day = 0, int grade = 0): event(name, year, month, day), grade(grade) {}
  void print_res() {
    std::cout << name << " " << year << " " << month << " " << day << " Grade " <<grade << std::endl;
  }
  void change_grade(int grade) {
    this->grade = grade;
  }

};

