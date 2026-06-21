#ifndef Dormitory_H
#define Dormitory_H
#include<vector>
#include<string>
#include<fstream>
#include"Room.h"
#include"student.h"
#include"Restaurant.h"
using namespace std;
class Dormitory
{
private:
string name;
int capacity;
vector<Room> rooms;
Restaurant restaurant;
int tookenRooms;
public:
Dormitory(const string& name, int capacity,const Restaurant& restaurant);
void addRoom(const Room& r);
bool assignStudent(Student* s);
bool removeStudent(int studentId);
void displayAvailableRooms()const;
Student* searchStudent_in_dormitory(int studentId);
int getRoomCount()const;
string getname()const;
int getCapacity() const;
int count_number_of_students_in_dor() const;
void saveRooms(ofstream &out)const;
void savedorms(ofstream &out);
void saveAssignments(ofstream &out, const string &dormName)const;
bool assignStudentToRoom(Student*, int roomNumber);
void saveRestaurant(ofstream &out) const;
void setRestaurantMenu(
    const string &breakfast,
    const string &lunch,
    const string &dinner
);
void showRestaurantMenu() const;
bool roomExists(int roomNumber) const;
bool removeRoom(int roomNumber);
};

#endif