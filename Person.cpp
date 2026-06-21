#include<iostream>
#include "Person.h"
#include<string>
using namespace std;
Person::Person (int id, string name):id(id),Fullname(name)
{}
void Person::display() const
{cout<<"\nthe name is"<<Fullname;
cout<<"\nthe student id is :"<<id;}
Person::~Person() {}