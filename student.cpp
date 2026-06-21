#include<iostream>
#include"student.h"
#include<string>
#include<fstream>
using namespace std;
Student:: Student(int d,string name,int year):Person(d, name), academicYear(year)
{ }
void Student::storeinfo(int d,string name,int year)
{
    id=(d>0)?d:0;
    Fullname=name;
    academicYear=(year>0)?year:0;
}

void Student::display()const 
{
    cout<<"the student's id : "<<id
    <<"\nthe student's name : "<<Fullname
    <<"\nthe acadenic year is : "<<academicYear<<endl;
    cout<<"============================="<<endl;
}

int Student::getId()const{return id;}
string Student::getfullname()const
{
    return Fullname;
}

ostream& operator<<(ostream& out,const Student& s)
{
    out<<"the student's id : "<<s.getId()
    <<"\nthe student's name : "<<s.getfullname()
    <<"\nthe acadenic year is : "<<s.getAcademicYear()<<endl;
    out<<"============================="<<endl;

    return out;
}

bool Student::operator==(const Student& other)
{
    return id == other.id;
}

void Student::save(ofstream &out)
{
    out << id << " " << Fullname << " " << academicYear << endl;
}
int Student::getAcademicYear()const
{return academicYear;}