#include <iostream>
#include "core/init.h"

using namespace std;

int main()
{
    Init::init();                       //Initializes dummy data to drive the program
    Menu* menu = Menu::getInstance();
    /* Gets an instance of Menu class to select views on runtime, the implementation is in core/menu.cpp */
    do {
        menu->display();                //Calls a method in Menu class, which calls other views
    }
    while (!EXIT_CODE);
    return 0;
}
