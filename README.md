# C++ OOP - Lesson 1

## Task

Your task is to implement the `Student` class in `EXERCISE.h`

You **do not** need to look at any other source code to complete the tasks. In
fact, unless you are familiar with template metaprogramming, you will find both
`main.cpp` and `private/Checker.h` to be _extremely_ confusing.

Implement the following:

## Part 1:

This covers writing a basic implementation.

### Data:

Your class should have two std::string data members:

`firstName` - an `std::string` holding the student's _first name_

`lastName` - an `std::string` holding the student's _last name_

**both** of these members should have`protected` visibility. Usually you would
make these private, but we'll need them this way for the purposes of this exercise.

### Constructors:

#### Default constructor
You should have a `public` default constructor that sets the first and last name to `Unknown`

#### Constructor with arguments:
You should have a `public` constructor that takes two arguments for the first name and last
name respectively and stores them into the data members mentioned above.

### Member Functions:

Both of the functions below should be `public`

#### FirstName()

This function should return a _reference_ to an `std::string` that is `const`.
The function should be callable from a `const` instance of `Student`.
The return value should of course be the data member holding the first name.

#### LastName()

This should work exactly the same as `FirstName()` but instead return the student's
last name.

## Part 2

This covers overloads and is something of a stretch goal.

### `FirstName()` setter.

Write a new overload of `FirstName()`. It should return `Student&`
(a reference to itself) and take an `std::string` which it should use to overwrite
 the student's first name.

### `LastName()` setter.

This should do exactly the same as the above for `FirstName()` but instead, set
the student's last name.

### `operator==`

Create a comparison operator which returns `true` if both the first and last
names are the same. otherwise, return `false`.
