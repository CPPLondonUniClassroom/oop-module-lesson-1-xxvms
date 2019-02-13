#pragma once
#include <string>

class Student {

protected:
  std::string firstName{};
  std::string lastName{};

public:
    Student(): firstName("Unknown"), lastName("Unknown"){}
    Student(std::string firstName_, std::string lastName_): firstName(firstName_), lastName(lastName_){}

    const std::string& FirstName() const {
      return firstName;
    }const std::string& LastName() const { return lastName; }


    Student &FirstName(const std::string firstName) {
      this->firstName = firstName;
      return *this;
    }

    Student &LastName(const std::string lastName) {
      this->lastName = lastName;
      return *this;
    }

    bool operator==(const Student& rhs )const {

      return this->firstName == rhs.firstName and this->lastName == rhs.lastName;
    }
};


/*

FirstName() setter.

Write a new overload of FirstName(). It should return Student& (a reference to itself) and take an std::string which it should use to overwrite the student's first name.

LastName() setter.

This should do exactly the same as the above for FirstName() but instead, set the student's last name.

operator==

    Create a comparison operator which returns true if both the first and last names are the same. otherwise, return false.

*/