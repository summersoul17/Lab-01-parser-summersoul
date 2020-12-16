//Copyright 2020 summersoul17 <17summersoul17@gmail.com>
#ifndef LAB_01_PARSER_STUDENT_HEADER
#define LAB_01_PARSER_STUDENT_HEADER

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

struct Student{

  private:
    string name;
    any group;
    any avg;
    any debt;

  public:
    Student(string name_, any group_, any avg_, any debt_)
      : name(name_), group(group_), avg(avg_), debt(debt_){};
    Student();

  friend void Print(const vector<Student> &students, ostream &info);
  static vector<Student> ParseFile(string jsonPath);
  static vector<Student> ParseString(string jsonString);

  static void Print(const vector<Student> &students, ostream &info);

};

#endif // LAB_01_PARSER_STUDENT_HEADER