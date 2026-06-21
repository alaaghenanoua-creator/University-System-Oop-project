#ifndef Room_H
#define Room_H
#include<vector>
#include"student.h"

using namespace std;
class Room
{
    private:
    int roomNumber;
    int capacity;
    vector<Student*> students;
    int actualNumber;
   public:
   Room(int n,int c);
   bool addSudent(Student* s);
   void displayRoom()const;
   bool removeStudent(int studentId);
   bool isFull()const;
   Student* searchStudent(int studentId)const;
   int number_of_students()const;
   int getroomNumber()const;
   int getCapacity()const;
   const vector<Student*>& getStudents() const;

};

#endif