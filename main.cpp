#include <iostream>
#include "Menu.h"
#include "Record.h"
#include <string>
#include <list>
using namespace std;

struct Char
{
    Char() : c(0) {}
    Char(char _c) : c(_c) {}
    Char(const Char& _char) : c(_char.c) {}

    bool operator==(Char _char) {return (c == _char.c);}
    bool operator<(Char _char) {return (c < _char.c);}
    char c;
    unsigned int getKey() const {return (unsigned int) c;}
};

int main()
{
//    HashTable<Student> h;
//    h.insert(Student(string("20026373"), string("YI bairen"), 1, 'F'));
//    h.insert(Student(string("20026374"), string("YI bairen"), 1, 'F'));
//    h.insert(Student(string("20026373"), string("YI bairen"), 1, 'F'));
//    list<Student> l = h.items();
//    for(list<Student>::iterator i = l.begin(); i != l.end(); ++i)
//    {
//        cout << i->getID() << endl;
//        cout << i->getName() << endl;
//        cout << i->getYear() << endl;
//        cout << i->getGender() << endl;
//    }
    MainMenu mainMenu;
    mainMenu.go();
    return 0;
}

