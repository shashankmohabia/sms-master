//
// Created by Ajat Prabha on 22-11-2017.
//

#ifndef SMS_ATTENDANCE_H
#define SMS_ATTENDANCE_H

#include "../core/auth/user.h"
#include "../courses/courses.h"
#include <iomanip>

using namespace std;

class Attendance {
    static map<string,
               map<string,
                   vector<bool>>> attendance_record;    //A map containing attendance of all Courses of all Users.
public:
    static void show_attendance(const string&);
    //Displays attendance of all the Courses of a particular User.

    static void update_attendance(const string&, const string&, bool);
    //Updates attendance of a particular User of a particular day of a particular Course.

    static map<string, map<string, vector<bool>>>& all();
    //Returns all the saved attendance records

    static void show_attendance_course(const string&);
    //Shows attendance record for a particular User object
};

#endif //SMS_ATTENDANCE_H
