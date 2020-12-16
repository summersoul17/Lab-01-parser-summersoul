//Copyright 2020 summersoul17 <17summersoul17@gmail.com>
#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <any>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <iomanip>

using std::vector;
using std::string;
using std::any;
using std::cout;
using std::cin;
using std::endl;
using json = nlohmann::json;
using std::ifstream;
using std::ostream;
using std::setw;
using std::left;
using std::right;
using std::stringstream;
using std::any_cast;
using std::nullptr_t;

struct Student{
  private:
    string name;
    any group;
    any avg;
    any debt;

  public:
    Student(string name_, any group_, any avg_, any debt_)
      : name(name_), group(group_), avg(avg_), debt(debt_){}
    Student();

  friend void Print(const vector<Student> &students, ostream &info);
  static vector<Student> ParseFile(string jsonPath);
  static vector<Student> ParseString(string jsonString);

  static void Print(const vector<Student> &students, ostream &info);
};
#endif // INCLUDE_STUDENT_HPP_
