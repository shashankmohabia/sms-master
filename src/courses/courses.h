//
// Created by Shashank Mohabia on 11/18/2017.
//

#ifndef SMS_COURSES_H
#define SMS_COURSES_H

#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include "../core/auth/user.h"

using namespace std;

class CourseError {
private:
    string _err;
public:
    explicit CourseError(const string&);
    string print_error();
};
class Course {
    static map<string, Course> course_list;             //A map containing all the courses
    static char timetable_map[6][4];                    //A timetable mapping to store slots
    string name, instructor_username;
    int year;
    char slot;
public:
    Course();
    //Default Constructor

    Course(const string&, const char&, const string&, int);
    //Constructor

    Course(const char*, const char&, const char*, int);

    ~Course() = default;
    //Default Destructor

    bool remove();
    //Removes a course from course_list.

    static bool show_user_courses(int);
    //Prints the Courses of a particular user/year.

    void save();
    //Saves a Course to course_list

    static map<string, Course>& all();
    //Returns course_list(all the courses)

    char get_slot();
    //Returns the Slot of a Course

    int get_year();
    //Returns the Year of a Course

    string get_instructor_name();
    //Returns the name of Course Instructor

    string get_course_name();
    //Returns name of Course

    static void show_timetable();
    //Prints timetable

    static void update_timetable();
    //Updates/changes the timetable
};

#endif //SMS_COURSES_H
