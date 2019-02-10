#include <iostream>
#include "private/Checker.h"
#include "EXERCISE.h"

using namespace std::string_literals;

using chk = StudentChecker<Student>;

static bool anyError = false;
static bool anyError2 = false;

template <typename T>
void checkDefaultConstructedFirstName() {
    T s;
    if (s.FirstName() != "Unknown") {
        std::cout << "ERROR: A default-constructed Student does not have 'Unknown' as their first name\n";
        anyError = true;
    }
}

template <typename T>
void checkDefaultConstructedLastName() {
    T s;
    if (s.LastName() != "Unknown") {
        std::cout << "ERROR: A default-constructed Student does not have 'Unknown' as their last name\n";
        anyError = true;
    }
}

template <typename T>
void checkStrConstructedFirstName() {
    T s{"John"s, "Doe"s};
    if (s.FirstName() != "John") {
        std::cout
                << "ERROR: a Student constructed with 'John' as first name does not return the same from FirstName()\n";
        anyError = true;
    }
}

template <typename T>
void checkStrConstructedLastName() {
    T s{"John"s, "Doe"s};
    if (s.LastName() != "Doe") {
        std::cout << "ERROR: a Student constructed with 'Doe' as last name does not return the same from LastName()\n";
        anyError = true;
    }
}

template <typename T>
void checkFNSetter() {
    T s{};
    if (s.FirstName("Joey"s).FirstName() != "Joey") {
        std::cout << "ERROR: First name did not match after setting it to 'Joey' in FirstName() setter\n";
        anyError2 = true;
    }
}

template <typename T>
void checkLNSetter() {
    T s{};
    if (s.LastName("Bloggs"s).LastName() != "Bloggs") {
        std::cout << "ERROR: Last name did not match after setting it to 'Bloggs' in LastName() setter\n";
        anyError2 = true;
    }
}

template <typename T>
void checkCmpOperator() {
    T s{"John"s, "Doe"s};
    T s2{"NotJohn"s, "NotDoe"s};
    if (s == s2) {
        std::cout << "ERROR: 'John Doe' is considered the same as 'NotJohn NotDoe' by operator==\n";
        anyError2 = true;
    }
    if ((s == s) == false) {
        std::cout << "ERROR: 'John Doe' is considered NOT the same as itself by operator==\n";
        anyError2 = true;
    }
    T s3{"John"s, "Doe"s};
    if ((s == s3) == false) {
        std::cout << "ERROR: 'John Doe' is considered NOT the same as another instance with the same data by operator==\n";
        anyError2 = true;
    }
}

int main() {
    if constexpr (chk::has_firstname) {
        if constexpr (chk::has_default_constructor)
            checkDefaultConstructedFirstName<Student>();
        if constexpr (chk::has_str_constructor)
            checkStrConstructedFirstName<Student>();
    } else {
        std::cout << "ERROR: FirstName member function not defined or type is incorrect\n";
        anyError = true;
    }
    if constexpr (chk::has_lastname) {
        if constexpr (chk::has_default_constructor)
            checkDefaultConstructedLastName<Student>();
        if constexpr (chk::has_str_constructor)
            checkStrConstructedLastName<Student>();
    } else {
        std::cout << "ERROR: LastName member function not defined or type is incorrect\n";
        anyError = true;
    }
    if constexpr (!chk::has_prot_firstName) {
        std::cout << "ERROR: firstName data member not defined or not marked as protected\n";
        anyError = true;
    }
    if constexpr (!chk::has_prot_lastName) {
        std::cout << "ERROR: lastName data member not defined or not marked as protected\n";
        anyError = true;
    }
    if constexpr (!chk::has_default_constructor) {
        std::cout << "ERROR: Student class does not have a default constructor\n";
        anyError = true;
    }
    if constexpr (!chk::has_str_constructor) {
        std::cout << "ERROR: Student does not have a constructor taking 2 std::string for first and last name\n";
        anyError = true;
    }
    if (!anyError) {
        std::cout << "You have passed part1 of the exercise!\n";

        if constexpr (chk::has_fn_setter) {
            if constexpr (chk::has_str_constructor && chk::has_firstname)
                checkFNSetter<Student>();
        } else {
            std::cout << "ERROR: Student does not have a FirstName() setter or its type is incorrect\n";
            anyError2 = true;
        }

        if constexpr (chk::has_ln_setter) {
            if constexpr (chk::has_str_constructor && chk::has_lastname)
                checkLNSetter<Student>();
        } else {
            std::cout << "ERROR: Student does not have a LastName() setter or its type is incorrect\n";
            anyError2 = true;
        }

        if constexpr (chk::has_cmp_operator) {
            if constexpr (chk::has_str_constructor)
                checkCmpOperator<Student>();
        } else {
            std::cout << "ERROR: Student does not have an operator== or its type is incorrect\n";
            anyError2 = true;
        }
        if (!anyError2)
            std::cout << "You have passed part2 of the exercise!\n";
    } else
        std::cout << "Part 2 not evaluated as you have not completed part 1.\n";
}