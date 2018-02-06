//
// Created by Ajat Prabha on 16-11-2017.
//

#include "init.h"

//Initialising global values
bool EXIT_CODE = false;
VIEW_CHOICES view_choice = VIEW_CHOICES(SPLASH);

void Init::init()
{
    /* Dummy data to drive the program */
    User user("student", "Ajat", "Prabha");
    user.set_password("spassword");
    user.set_year(1);
    User user1("admin", "Shashank", "Mohabia");
    user1.set_password("apassword");
    user1.make_superuser();
    try {
        user.save();
        user1.save();
    }
    catch (UserError& e) {
        cout << e.print_error() << endl;
    }
    Course course("Linear", 'A', "admin", 1), course1("Physics", 'B', "admin", 1), course2("Chemistry", 'D', "admin",
            1);
    try {
        course.save();
        course1.save();
        course2.save();
    }
    catch (CourseError& e) {
        cout << e.print_error() << endl;
    }
    Attendance::update_attendance(user.get_username(), course.get_course_name(), false);
    Attendance::update_attendance(user.get_username(), course.get_course_name(), true);
    Attendance::update_attendance(user.get_username(), course.get_course_name(), false);
}
