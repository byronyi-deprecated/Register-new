#include <iostream>
#include "Menu.h"
#include "Record.h"
#include <string>
#include <list>
using namespace std;

/*
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
*/

int main()
{
    MainMenu mainMenu;
    mainMenu.go();
    return 0;
}

