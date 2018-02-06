//
// Created by Ajat Prabha and Shashank Mohabia on 11/20/2017.
//

#ifndef SMS_VIEW_H
#define SMS_VIEW_H

#include <iomanip>
#include <cstdlib>
#include <iomanip>
#include "init.h"
#include "auth/user.h"
#include "../courses/courses.h"
#include "../attendance/attendance.h"

using namespace std;

//An abstract base class which provides interface to other derived classes
class View {
public:
    View() = default;                       //Default constructor
    virtual void display();                 //An interface to call the display() method of derived classes
    void format_output(const string&);      //Formats the passed string to center it in the console
    virtual ~View() = default;              //default virtual destructor
};

extern View* global_view;           //Makes an environment variable to store a pointer to current variable

class SplashView: public View {
public:
    SplashView() = default;
    void display() override;
    ~SplashView() override = default;
};
class LoginView: public View {
public:
    LoginView() = default;
    void display() override;
    ~LoginView() override = default;
};
class RegisterView: public View {
public:
    RegisterView() = default;
    void display() override;
    ~RegisterView() override = default;
};
class StudentDetailView: public View {
public:
    StudentDetailView() = default;
    void display() override;
    ~StudentDetailView() override = default;
};
class AdminDetailView: public View {
public:
    AdminDetailView() = default;
    void display() override;
    ~AdminDetailView() override = default;
};

#endif //SMS_VIEW_H
