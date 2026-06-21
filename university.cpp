#include<vector>
#include<string>
#include"Room.h"
#include"student.h"
#include"Restaurant.h"
#include"Dormitory.h"
#include<iostream>
#include "University.h"
#include<fstream>
using namespace std;
void University::addDormitory(const Dormitory& dormitory)
{dormitories.push_back(dormitory);}


bool University::removeDormitory(const string& dormitoryName)
{
    for(auto it = dormitories.begin();
         it != dormitories.end();
         ++it)
    {
        if(it->getname() == dormitoryName)
        {
            dormitories.erase(it);
            return true;
        }
    }

    cout << "there is no dormitory with this name\n";
    return false;
}


int University::getTotalDormitories() const
{
    return dormitories.size();
}

int University::getTotalRooms() const
{
    int total = 0;

    for (const Dormitory& dormitory : dormitories)
        total += dormitory.getRoomCount();

    return total;
}

int University::getTotalStudents() const
{
    int total = 0;

    for (const Dormitory& dormitory : dormitories)
        total += dormitory.count_number_of_students_in_dor();

    return total;
}

void University::displayStatistics() const
{
    cout << "Dormitories: "
         << getTotalDormitories() << endl;

    cout << "Rooms: "
         << getTotalRooms() << endl;

    cout << "Students: "
         << getTotalStudents() << endl;
}

Student* University::search_Student(int studentId)
{
    for (auto &s : students)
    {
        if (s.getId() == studentId)
            return &s;
    }
    return nullptr;
}
void University::addStudent(int id, string name, int year)
{
    // optional: prevent duplicate IDs
    for (const Student &s : students)
    {
        if (s.getId() == id)
        {
            cout << "Student with this ID already exists\n";
            return;
        }
    }

    // add student safely
    students.emplace_back(id, name, year);
}


bool University::assignStudentToDormitory(int studentId, const string& dormName)
{

    for(auto& d : dormitories)
    {
        if(d.searchStudent_in_dormitory(studentId))
        {
            cout<<"Student already assigned\n";
            return false;
        }
    }
    // 1. find student in university
    Student* student = search_Student(studentId);

    if (!student)
    {
        cout << "Student not found\n";
        return false;
    }

    // 2. find dormitory
    for (Dormitory &dorm : dormitories)
    {
        if (dorm.getname() == dormName)
        {
            // 3. assign student to dormitory (inside rooms)
            bool success = dorm.assignStudent(student);

            if (!success)
                cout << "No available room in dormitory\n";

            return success;
        }
    }

    cout << "Dormitory not found\n";
    return false;
}

void University::saveAssignments(ofstream &out)
{
    for (const Dormitory &d : dormitories)
    {
        string dormName = d.getname();

        d.saveAssignments(out, dormName);
    }
}

void University::loadStudents()
{
    ifstream in("students.txt");

    int id, year;
    string name;

    while (in >> id >> name >> year)
    {
        students.emplace_back(id, name, year);
    }

    in.close();
}

void University::loadDormitories()
{
    ifstream in("dormitories.txt");

    string name;
    int capacity;

    while (in >> name >> capacity)
    {
        Dormitory d(name, capacity, Restaurant("", "", ""));
        dormitories.push_back(d);
    }

    in.close();
}

void University::loadRooms()
{
    ifstream in("rooms.txt");

    string dormName;
    int roomNumber, capacity;

    while (in >> dormName >> roomNumber >> capacity)
    {
        for (Dormitory &d : dormitories)
        {
            if (d.getname() == dormName)
            {
                Room r(roomNumber, capacity);
                d.addRoom(r);
            }
        }
    }

    in.close();
}

void University::loadAssignments()
{
    ifstream in("assignments.txt");

    int studentId;
    string dormName;
    int roomNumber;

    while (in >> studentId >> dormName >> roomNumber)
    {
        Student* s = search_Student(studentId);

        if (!s) continue;

        for (Dormitory &d : dormitories)
        {
            if (d.getname() == dormName)
            {
                d.assignStudentToRoom(s, roomNumber); // we will fix this next
            }
        }
    }

    in.close();
}

void University::loadAll()
{
    students.clear();
    dormitories.clear();

    loadStudents();
    loadDormitories();
    loadRooms();
    loadRestaurants();
    loadAssignments();
}
void University::saveStudents(ofstream &out)
{
    for (const Student &s : students)
    {
        out << s.getId() << " "
            << s.getfullname() << " "
            << s.getAcademicYear()
            << endl;
    }
}
void University::saveRooms(ofstream &out)
{
    for (const Dormitory &d : dormitories)
    {
        d.saveRooms(out);
    }
}
void University::saveDormitories(ofstream &out)
{
    for (const Dormitory &d : dormitories)
    {
        out << d.getname() << " "
            << d.getCapacity()
            << endl;
    }
}
void University::saveAll()
{
    ofstream s1("students.txt");
    ofstream s2("dormitories.txt");
    ofstream s3("rooms.txt");
    ofstream s4("assignments.txt");
    ofstream s5("restaurants.txt");

    saveStudents(s1);
    saveDormitories(s2);
    saveRooms(s3);
    saveAssignments(s4);
    saveRestaurants(s5);

    s1.close();
    s2.close();
    s3.close();
    s4.close();
    s5.close();
}
bool University::removeStudent(int studentId)
{
    // remove from all dormitories first
    for (Dormitory &d : dormitories)
    {
        d.removeStudent(studentId);
    }

    for (auto it = students.begin();
         it != students.end();
         ++it)
    {
        if (it->getId() == studentId)
        {
            students.erase(it);
            return true;
        }
    }

    return false;
}

void University::saveRestaurants(ofstream &out)
{
    for (const Dormitory &d : dormitories)
    {
        d.saveRestaurant(out);
    }
}

void University::loadRestaurants()
{
    ifstream in("restaurants.txt");

    string dormName;
    string breakfast;
    string lunch;
    string dinner;

    while (in >> dormName >> breakfast >> lunch >> dinner)
    {
        for (Dormitory &d : dormitories)
        {
            if (d.getname() == dormName)
            {
                d.setRestaurantMenu(
                    breakfast,
                    lunch,
                    dinner
                    );
            }
        }
    }

    in.close();
}

bool University::addRoomToDormitory(const string& dormName, int roomNumber, int capacity)
{
    for (Dormitory &d : dormitories)
    {
        if (d.getname() == dormName)
        {
            if (d.roomExists(roomNumber))
            {
                cout << "Room already exists in this dormitory\n";
                return false;
            }

            Room r(roomNumber, capacity);
            d.addRoom(r);
            return true;
        }
    }

    cout << "Dormitory not found\n";
    return false;
}

bool University::assignStudentToRoom(int studentId, const string& dormName, int roomNumber)
{
    
    for (auto& d : dormitories)
    {
        if (d.searchStudent_in_dormitory(studentId))
        {
            cout << "Student already assigned\n";
            return false;
        }
    }

    Student* student = search_Student(studentId);
    if (!student)
    {
        cout << "Student not found\n";
        return false;
    }

    for (Dormitory &dorm : dormitories)
    {
        if (dorm.getname() == dormName)
        {
            return dorm.assignStudentToRoom(student, roomNumber);
        }
    }

    cout << "Dormitory not found\n";
    return false;
}

bool University::removeRoomFromDormitory(const string& dormName, int roomNumber)
{
    for (Dormitory &d : dormitories)
    {
        if (d.getname() == dormName)
        {
            return d.removeRoom(roomNumber);
        }
    }

    cout << "Dormitory not found\n";
    return false;
}