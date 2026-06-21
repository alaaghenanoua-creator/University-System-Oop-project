#ifndef student_H
#define student_H
#include<string>
#include "Person.h"
using namespace std;
class Student:public Person
{
    private:
    int academicYear;
    public:
    Student(int d,string name,int year);
    int getId()const;
    void storeinfo(int d,string name,int year);
    bool operator==(const Student& other);
    void display()const override;
    string getfullname()const;
    void save(ofstream &out);
    int getAcademicYear()const;
    friend ostream& operator<<(ostream& out,const Student& s);
};













#endif