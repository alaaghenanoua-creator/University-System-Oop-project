#ifndef university_H
#define university_H
#include<vector>
#include<string>
#include<fstream>
#include"Room.h"
#include"student.h"
#include"Restaurant.h"
#include"Dormitory.h"
using namespace std;
class University
{
    private:
    vector<Dormitory> dormitories;
    vector<Student> students;

 public:
   void addDormitory(const Dormitory& dormitory);
   bool removeDormitory(const string& dormitoryName);
   Student* search_Student(int studentId);
   int getTotalDormitories() const;
   int getTotalRooms() const;
   int getTotalStudents() const;
   void displayStatistics() const;
   void addStudent(int id, string name, int year);
   bool assignStudentToDormitory(int studentId, const string& dormName);
   void saveAssignments(ofstream &out);
   void loadStudents();
   void loadDormitories();
   void loadRooms();
   void loadAssignments();
   void loadAll();
   void saveAll();
   void saveStudents(ofstream &out);
   void saveDormitories(ofstream &out);
   void saveRooms(ofstream &out);
   bool removeStudent(int studentId);
   void saveRestaurants(ofstream &out);
   void loadRestaurants();
   template<typename T>
   T* findById(vector<T>& vec, int id)
{  for (auto& item : vec)
    {  if (item.getId() == id)
       return &item;
    }
return nullptr;
}
   bool addRoomToDormitory(const string& dormName, int roomNumber, int capacity);
   bool assignStudentToRoom(int studentId, const string& dormName, int roomNumber);
   bool removeRoomFromDormitory(const string& dormName, int roomNumber);
};

#endif