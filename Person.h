#ifndef Person_H
#define Person_H
#include<string>
using namespace std;
class Person
{
protected:
    int id;
    string Fullname;

public:
    Person(int id, string name);
    virtual void display() const;
    virtual ~Person();
};


#endif