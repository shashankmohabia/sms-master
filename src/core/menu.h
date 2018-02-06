//
// Created by Ajat Prabha on 22-11-2017.
//

#ifndef SMS_MENU_H
#define SMS_MENU_H

extern bool START;      //Makes environment variable to manage call to SplashView class

class Menu {
public:
    static Menu* getInstance();
    //Returns an instance of Meu class to drive the views

    void display();
    //this methods decides which view to call
};

#endif //SMS_MENU_H
