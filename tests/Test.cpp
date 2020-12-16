// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include <string>
#include <Student.hpp>
using string = std::string;

TEST(ParseTest, TableTest){
  string wrong_string =
      R"({
  "items": [
    {
      "name": "Jmishenko Valeriy",
      "group": "9",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Vitaliy Tsal",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Evgeniy Ponasenkov",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
  auto students = Student::ParseString(wrong_string);

  stringstream ss;

  Student::Print(students, ss);

  string expect_string = R"(| name              | group | avg | debt   |
|-------------------|-------|-----|--------|
| Jmishenko Valeriy | 9     | 4.25| null   |
|-------------------|-------|-----|--------|
| Vitaliy Tsal      | 31    | 4   | C++    |
|-------------------|-------|-----|--------|
| Evgeniy Ponasenkov| IU8-31| 3.33| 3 items|
|-------------------|-------|-----|--------|
)";
  EXPECT_EQ(ss.str(), expect_string);
}

TEST(ParseTest, ErrorFileOpening){

  EXPECT_THROW(Student::ParseFile("file.json"), std::runtime_error);
}

TEST(ParseTest, ErrorStringParsing){
  string raw_string = R"({
  "items": {
    "IsWrongField" : true
  },
  "_meta": {
    "count": 3
  }
})";

  EXPECT_THROW(Student::ParseString(raw_string), std::runtime_error);
}

TEST(ParseTest, ErrorStringCount){
  string raw_string = R"({
  "items": [
    "Apples",
    "Bananas"
  ],
  "_meta": {
    "count": 3
  }
})";

  EXPECT_THROW(Student::ParseString(raw_string), std::runtime_error);
}

TEST(ParseTest, ErrorFileCount){
  string student = R"({
  "items": [
    "Apples",
    "Bananas"
  ],
  "_meta": {
    "count": 3
  }
})";

  std::ofstream wrong_file;
  wrong_file.open("wrong_file.json");
  wrong_file << student;
  wrong_file.close();

  EXPECT_THROW(Student::ParseFile("wrong_file.json"),std::runtime_error);
}

TEST(ParseTest, ErrorFileArray){
  string raw_string = R"({
  "items": {
    "IsWrongField" : true
  },
  "_meta": {
    "count": 3
  }
})";

  std::ofstream wrong_file;
  wrong_file.open("wrong_file.json");
  wrong_file << raw_string;
  wrong_file.close();

  EXPECT_THROW(Student::ParseFile("wrong_file.json"), std::runtime_error);
}

TEST(ParseTest, RightFileParsing){
  string json_string =
      R"({
  "items": [
    {
      "name": "Jmishenko Valeriy",
      "group": "9",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Vitaliy Tsal",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Evgeniy Ponasenkov",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";

  std::ofstream wrong_file;
  wrong_file.open("wrong_file.json");
  wrong_file << json_string;
  wrong_file.close();

  auto students = Student::ParseFile("wrong_file.json");

  stringstream ss;

  Student::Print(students, ss);

  string right_string = R"(| name              | group | avg | debt   |
|-------------------|-------|-----|--------|
| Jmishenko Valeriy | 9     | 4.25| null   |
|-------------------|-------|-----|--------|
| Vitaliy Tsal      | 31    | 4   | C++    |
|-------------------|-------|-----|--------|
| Evgeniy Ponasenkov| IU8-31| 3.33| 3 items|
|-------------------|-------|-----|--------|
)";

  EXPECT_EQ(right_string, ss.str());
}