//Copyright 2020 summersoul17 <17summersoul17@gmail.com>
#include <Student.hpp>

string getString(any value);

string get_name(const json& value);
any get_avg(const json& value);
any get_group(const json& value);
any get_debt(const json& value);

vector<Student> Student::ParseFile(
    string jsonPath) {
  ifstream jFile(jsonPath);

  if (!jFile) {
    throw std::runtime_error{"File can not be opened."};
  }

  json data;

  jFile >> data;

  if (!(data["items"].is_array())) {
    throw std::runtime_error{"Field \"items\" is not array!"};
  }

  if (data["items"].size() != (data["_meta"])["count"]) {
    throw std::runtime_error{"Field \"items\" is incorrect, check \"_meta\""};
  }

  vector<Student> vectorStudent;

  for (const auto& student : data["items"]) {
    string s_name = get_name(student["name"]);
    any s_avg = get_avg(student["avg"]);
    any s_group = get_group(student["group"]);
    any s_debt = get_debt(student["debt"]);

    Student temp(s_name, s_group, s_avg, s_debt);

    vectorStudent.emplace_back(temp);
  }

  return vectorStudent;
}

vector<Student> Student::ParseString(string jsonString) {
  json data = json::parse(jsonString);

  if (!(data["items"].is_array())) {
    throw std::runtime_error{"Field \"items\" is not array!"};
  }

  if (data["items"].size() != (data["_meta"])["count"]) {
    throw std::runtime_error{"Field \"items\" is incorrect, check \"_meta\""};
  }

  vector<Student> vectorStudent;

  for (const auto& student : data["items"]) {
    string s_name = get_name(student["name"]);
    any s_avg = get_avg(student["avg"]);
    any s_group = get_group(student["group"]);
    any s_debt = get_debt(student["debt"]);

    Student temp(s_name, s_group, s_avg, s_debt);

    vectorStudent.emplace_back(temp);
  }
  return vectorStudent;
}

string get_name(const json& value) { return value.get<string>(); }

any get_avg(const json& value) {
  if (value.is_string()) {
    return value.get<string>();
  } else if (value.is_number_integer()) {
    return value.get<int>();
  } else {
    return value.get<double>();
  }
}

any get_group(const json& value) {
  if (value.is_string()) {
    return value.get<string>();
  }
  else
    return value.get<int>();
}

any get_debt(const json& value) {
  if (value.is_null()) {
    return nullptr;
  }
  else if (value.is_string()) {
    return value.get<string>();
  }
  else
    return value.get<vector<string>>();
}

string get_string(any value) {
  if (value.type() == typeid(nullptr_t)) {
    return "null";
  }
  else if (value.type() == typeid(int)) {
    stringstream out;
    out << any_cast<int>(value);
    return out.str();
  }
  else if (value.type() == typeid(string)) {
    return any_cast<string>(value);
  }
  else if (value.type() == typeid(double)) {
    stringstream out;
    out << any_cast<double>(value);
    return out.str();
  }
  else {
    stringstream out;
    out << any_cast<vector<string>>(value).size() << " items";
    return out.str();
  }
}

void Student::Print(const vector<Student>& students, ostream& info) {
  vector<size_t> width = {0, 0, 0, 0};

  for (size_t i = 0; i < students.size(); ++i) {
    if (students[i].name.length() > width[0]) {
      width[0] = students[i].name.length();
    }
    if (get_string(students[i].group).length() > width[1]) {
      width[1] = get_string(students[i].group).length();
    }
    if (get_string(students[i].avg).length() > width[2]) {
      width[2] = get_string(students[i].avg).length();
    }
    if (get_string(students[i].debt).length() > width[3]) {
      width[3] = get_string(students[i].debt).length();
    }
  }

  string borderSymbol;

  for (size_t i = 0; i < width.size(); ++i) {
    borderSymbol += "|-";
    for (size_t j = 0; j < width[i]; ++j) {
      borderSymbol += "-";
    }
  }
  borderSymbol += "|";

  info << "| " << left << setw(width[0]) << "name";
  info << "| " << left << setw(width[1]) << "group";
  info << "| " << left << setw(width[2]) << "avg";
  info << "| " << left << setw(width[3]) << "debt"
       << "|" << endl;
  info << right << borderSymbol << endl;

  for (auto& student : students) {
    info << "| " << left << setw(width[0]) << student.name;
    info << "| " << left << setw(width[1]) << get_string(student.group);
    info << "| " << left << setw(width[2]) << get_string(student.avg);
    info << "| " << left << setw(width[3]) << get_string(student.debt) << "|"
         << endl;
    info << right << borderSymbol << endl;
  }
}
