// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include <string>
#include <Student.hpp>
using string = std::string;

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(WrongString, WrongCount){
  const char wrong_string[] =
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
  Student::Print(students, cout);
}

