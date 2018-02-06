//
// Created by Ajat Prabha on 03-10-2017.
//
#ifndef SMS_USER_H
#define SMS_USER_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <set>
#include <fstream>
#include <vector>

using namespace std;

class UserError {
private:
    string _err;
public:
    explicit UserError(const string&);
    string print_error();
};

class User {
    static map<string, User> object_list;
    int _year;
    //map<char, Courses> _course_set;
    map<string, int> _attendance;
protected:
    bool _superuser_status;
    string _username, _first_name, _last_name, _password;
public:
    User();
    //Default Constructor

    User(const string&, const string&, const string&);
    //Parametrized Constructor

    User(const char*, const char*, const char*);
    //Overloaded Constructor

    static map<string, User>& all();
    //Returns the userlist

    string get_username() const;
    //Returns username

    virtual bool is_anonymous();
    //Returns whether the user is anonymous or not

    virtual bool is_authenticated();
    //Returns whether the user is registered or not

    string get_fullname() const;
    //Returns the full name of user

    string get_shortname() const;

    virtual void make_superuser();
    //Function to make a function super user

    virtual bool is_superuser();
    //Returns whether the user is super user or not

    void set_username(const string& /* unused */);

    int get_year();
    //returns the year of a student

    void set_year(int);
    //sets the value of a year

    virtual void set_password(const string&);
    //sets the password of a year

    virtual bool check_password(const string&);

    User& save();

    bool remove();
    //Removes a user from objectlist

};

extern User* current_user;

class AnonymousUser: public User {
public:
    AnonymousUser();
    bool is_anonymous() final;
    bool is_authenticated() final;
    bool is_superuser() final;
    void set_password(const string& /*unused*/) final;
    bool check_password(const string& /*unused*/) final;
};

#endif //SMS_USER_H
