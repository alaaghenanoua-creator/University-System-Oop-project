#ifndef Restaurant_H
#define Restaurant_H
#include<string>
#include<fstream>
using namespace std;
class Restaurant
{
private:
string breakfast;
string lunch;
string dinner;
public:
void setbreakfast(string b);
void setlunch(string l);
void setdinner(string d);
Restaurant(string b,string l,string d);
void display()const;
void save(ofstream &out)const;
string getBreakfast() const;
string getLunch() const;
string getDinner() const;

};

#endif