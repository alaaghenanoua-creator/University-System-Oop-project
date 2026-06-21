#include<iostream>
#include"Restaurant.h"
#include<string>
#include<fstream>
using namespace std;
Restaurant::Restaurant(string b,string l,string d)
{    breakfast=b;
     lunch=l;
     dinner=d;  

}
void Restaurant::setbreakfast(string b)
{
     breakfast=b;
}
void Restaurant::setlunch(string l)
{
    lunch=l;
}
void Restaurant::setdinner(string d)
{
    dinner=d;  
}

void Restaurant::display() const
{
    cout << "Breakfast : "
         << breakfast << endl;

    cout << "Lunch : "
         << lunch << endl;

    cout << "Dinner : "
         << dinner << endl;
}
void Restaurant::save(ofstream &out)const
{
    out<<breakfast<<"   "<<lunch<<"   "<<dinner;
    out<<endl;
}

string Restaurant::getBreakfast() const
{
    return breakfast;
}

string Restaurant::getLunch() const
{
    return lunch;
}

string Restaurant::getDinner() const
{
    return dinner;
}