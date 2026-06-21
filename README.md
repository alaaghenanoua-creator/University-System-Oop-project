# University Management System

## Overview

The University Management System is a C++ Object-Oriented Programming (OOP) project developed using Qt Creator for the graphical user interface. The system simulates the management of a university environment by handling students, dormitories, rooms, and restaurants through well-structured classes and object relationships.

The project demonstrates the application of key OOP concepts such as encapsulation, inheritance, polymorphism, composition, operator overloading, and dynamic memory management.

## Project Structure

The system is organized into the following main classes:

* **Person**: Base class representing a person in the university.
* **Student**: Derived class that stores student information such as ID and name.
* **Room**: Represents a dormitory room and manages room occupancy.
* **Dormitory**: Manages a collection of rooms and student assignments.
* **Restaurant**: Represents university restaurants and their available meals.
* **University**: Central class responsible for managing students, dormitories, and restaurants.

## Features

* Student registration and management
* Dormitory creation and administration
* Room allocation for students
* Restaurant management
* Display of university information
* Use of inheritance and polymorphism
* Operator overloading for object display
* Modular and maintainable code design

## Technologies Used

* C++
* Object-Oriented Programming (OOP)
* Qt Creator IDE
* MinGW / GCC Compiler

## How to Build and Run

### Using Qt Creator

1. Open Qt Creator.
2. Select **File → Open File or Project**.
3. Open the project file (`.pro`).
4. Configure the project kit if prompted.
5. Click **Build** (Ctrl + B).
6. Click **Run** (Ctrl + R).

### Alternative Compilation (Command Line)

If all source files are available, the project can be compiled manually using GCC:

g++ main.cpp University.cpp Dormitory.cpp Room.cpp Student.cpp Restaurant.cpp Person.cpp -o UniversitySystem

## Author

Alaa Ghenanoua

