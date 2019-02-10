#pragma once

class Student {
protected:
    std::string firstName;
    std::string lastName;
public:
    Student() : firstName{"Unknown"}, lastName{"Unknown"} {}
    Student(std::string f, std::string l) : firstName{std::move(f)}, lastName{std::move(l)} {}
    const std::string& FirstName() const & noexcept {
        return firstName;
    }

    Student& FirstName(std::string newName) {
        firstName = std::move(newName);
        return *this;
    }

    Student& LastName(std::string newName) {
        lastName = std::move(newName);
        return *this;
    }

    const std::string& LastName() const & noexcept {
        return lastName;
    }

    bool operator==(const Student& other) const {
        return firstName == other.firstName && lastName == other.lastName;
    }
};
