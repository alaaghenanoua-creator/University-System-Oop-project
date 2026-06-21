#include<iostream>
#include"Room.h"
#include<vector>
#include"student.h"
#include<algorithm>
#include<fstream>
#include<exception>
using namespace std;
Room::Room(int n,int c)
{
    roomNumber=(n>0)?n:0;
    capacity=(c>0)?c:0;
    actualNumber=0;
}

bool Room::addSudent(Student* s)
{
    if(isFull())
        throw runtime_error("Room is full");

      for (Student* st : students)
    {
        if (st->getId() == s->getId())
            return false;
    }
    students.push_back(s);
    actualNumber++;

    return true;
}
   void Room::displayRoom()const
   {
     cout<<"the room number : "<<roomNumber<<endl;
      cout<<"the room capacity : "<<capacity<<endl;
      cout<<"the students :"<<endl;
     for(int i=0;i<actualNumber;i++)
     {
        students[i]->display();
        cout<<endl;
     }

   }

     bool Room::removeStudent(int studentId)
  {for(int i=0;i<actualNumber;i++)
    {if(students[i]->getId()==studentId)
     {students.erase(students.begin()+i);
      actualNumber--;
        return true;
     }
    }
    return false;
  }
  
   bool Room::isFull()const
   {
    return (actualNumber==capacity);
   }


Student* Room::searchStudent(int studentId)const
{
    for(int i=0 ;i<actualNumber;i++)
    {if(students[i]->getId()==studentId)
    return students[i];
    }
    return nullptr;
}
int Room::number_of_students()const
{return actualNumber;}


int Room::getroomNumber()const
{return roomNumber;}

int Room::getCapacity()const
{return capacity;}
const vector<Student*>& Room::getStudents() const
{
    return students;
}