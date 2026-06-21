#include<iostream>
#include<vector>
#include<string>
#include"Room.h"
#include"student.h"
#include"Restaurant.h"
#include "Dormitory.h"
#include<fstream>
#include <stdexcept>
using namespace std;
Dormitory::Dormitory(const string& name, int capacity,
                     const Restaurant& restaurant)
    : name(name),
    capacity(capacity),
    restaurant(restaurant)
{tookenRooms=0;
}
void Dormitory::addRoom(const Room& room)
{
    if (rooms.size() < capacity)
    {
        rooms.push_back(room);
        tookenRooms++;
    }
}
bool Dormitory::assignStudent(Student* student)
{   for (Room& room : rooms)
    {   try
        {   room.addSudent(student);
            return true;
        }
        catch(const exception& e)
        {
            cout << "Exception: " << e.what() << endl;
        }
    }
    return false;
}
bool Dormitory::removeStudent(int studentId)
{
    for (Room& room : rooms)
    {
        if( room.removeStudent(studentId))
            return true;
    }
    return false;
}
void Dormitory::displayAvailableRooms() const
{
    for (const Room& room : rooms)
    {
        if (!room.isFull())
        {
            room.displayRoom();
        }
    }
    cout<<"the number of available rooms is : "<<(capacity-tookenRooms);
}
Student* Dormitory::searchStudent_in_dormitory(int studentId)
{ for (Room& room : rooms)
    {
        Student* student=room.searchStudent(studentId);
        if(student!=nullptr)
        {return student;}
    }
    cout<<"the student doesn't exist in this dormitory\n";
    return nullptr;
}
int Dormitory::getRoomCount()const
{return tookenRooms;}
int Dormitory::count_number_of_students_in_dor()const
{int count=0;
    for(const Room& room : rooms)
    {count+=room.number_of_students();
    }
    return count;
}
string Dormitory::getname() const
{
    return name;
}
int Dormitory::getCapacity() const
{
    return capacity;
}
void Dormitory::saveRooms(ofstream &out) const
{
    for (const Room &r : rooms)
    {
        out << name << " "
            << r.getroomNumber() << " "
            << r.getCapacity()
            << endl;
    }
}
void Dormitory::savedorms(ofstream &out)
{
    string dormName = this->getname();
    for (Room& r : rooms)
    {
        out << name << " "
            << r.getCapacity()
            << " ";
    }
    cout<<endl;
}
void Dormitory::saveAssignments(ofstream &out, const string &dormName)const
{
    for (const Room &r : rooms)
    {
        int roomNumber = r.getroomNumber();
        const vector<Student*> &list = r.getStudents();
        for (Student* s : list)
        {
            out << s->getId() << " "
                << dormName << " "
                << roomNumber
                << endl;
        }
    }
}
bool Dormitory::assignStudentToRoom(Student* student, int roomNumber)
{
    // find the room
    for (Room &r : rooms)
    {
        if (r.getroomNumber() == roomNumber)
        {
            // check if room is full
            if (r.isFull())
            {
                cout << "Room is full\n";
                return false;
            }
            // add student
            r.addSudent(student);
            return true;
        }
    }
    cout << "Room not found\n";
    return false;
}
void Dormitory::saveRestaurant(ofstream &out) const
{
    out << name << " ";
    restaurant.save(out);
}
void Dormitory::setRestaurantMenu(
    const string &breakfast,
    const string &lunch,
    const string &dinner
    )
{
    restaurant.setbreakfast(breakfast);
    restaurant.setlunch(lunch);
    restaurant.setdinner(dinner);
}
void Dormitory::showRestaurantMenu() const
{
    restaurant.display();
}

// ============================================================
// NEW METHODS (added to support University::addRoomToDormitory
// and University::removeRoomFromDormitory). Nothing above this
// line was changed.
// ============================================================

bool Dormitory::roomExists(int roomNumber) const
{
    for (const Room &r : rooms)
    {
        if (r.getroomNumber() == roomNumber)
            return true;
    }
    return false;
}

bool Dormitory::removeRoom(int roomNumber)
{
    for (auto it = rooms.begin(); it != rooms.end(); ++it)
    {
        if (it->getroomNumber() == roomNumber)
        {
            if (it->number_of_students() > 0)
            {
                cout << "Cannot remove room: students are still assigned to it\n";
                return false;
            }
            rooms.erase(it);
            if (tookenRooms > 0) tookenRooms--;
            return true;
        }
    }
    cout << "Room not found\n";
    return false;
}