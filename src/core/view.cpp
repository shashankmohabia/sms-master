//
// Created by Ajat Prabha and Shashank Mohabia on 11/20/2017.
//

#include "view.h"

View* global_view = new View;

void View::display()
{
    /* display() interface */
}

void View::format_output(const string& s)
{
    int l = s.length();
    auto pos = (120-l)/2;
    for (int i = 0; i<pos; i++) {
        cout << " ";
    }
    cout << s << endl;
}

void SplashView::display()
{
    format_output("Welcome to Student Management System");
    cout << "\n";
    format_output("1. Login");
    format_output("0. Exit");
    int choice;
    cin >> choice;
    switch (choice) {
    case 1: {
        view_choice = VIEW_CHOICES(LOGIN);
        break;
    }
    case 0: {
        EXIT_CODE = true;
        break;
    }
    default: {
        START = true;
        break;
    }
    }
}

void LoginView::display()
{
    format_output("Welcome to login screen\n");
    format_output("Enter username");
    string username, password;
    cin >> username;
    format_output("Enter password");
    cin >> password;
    try {
        auto user = User::all().find(username);
        if (user!=User::all().end() && user->second.check_password(password)) {
            current_user = &(user->second);
            cout << current_user->get_fullname() << " successfully logged in" << endl;
        }
        else {
            cout << "Either username or password is incorrect\n";
            system("pause");
        }
    }
    catch (UserError& e) {
        cout << e.print_error() << endl;
    }
    if (current_user->is_authenticated()) view_choice = VIEW_CHOICES(DETAIL);
}

void RegisterView::display()
{
    format_output("Welcome to register screen");
    cout << "At present there are " << User::all().size() << " users in the system\n";
    string username, f_name, l_name, pass = "   $", c_pass = "     ";
    cout << "Enter Username, First Name, Last Name\n";
    cin >> username >> f_name >> l_name;
    User user(username, f_name, l_name);
    while (pass!=c_pass) {
        if (pass!="   $") {
            cout << "Password doesn't match, retry!" << endl;
        }
        cout << "Enter password" << endl;
        cin >> pass;
        cout << "Confirm password" << endl;
        cin >> c_pass;
    }
    user.set_password(pass);
    char ch;
    user_type_choice:
    cout << "Do you want to make this user a superuser?\n1. Yes\n2. No\n";
    cin >> ch;
    switch (ch) {
    case '1':user.make_superuser();
        break;
    case '2': {
        cout << "Enter year of student: \n";
        int year;
        cin >> year;
        user.set_year(year);
        break;
    }
    default: {
        cout << "Please enter a valid choice. \n";
        goto user_type_choice;
    }
    }
    try {
        user.save();
        cout << user.get_fullname() << " successfully registered" << endl;
        cout << "Now there are " << User::all().size() << " users in the system" << endl;
        view_choice = VIEW_CHOICES(DETAIL);
    }
    catch (UserError& e) {
        cout << e.print_error() << endl;
    }
}

void StudentDetailView::display()
{
    string header = "Welcome "+current_user->get_fullname();
    format_output(header);
    format_output("1. Show Timetable");
    format_output("2. Show Attendance");
    format_output("3. Show Course List");
    format_output("4. Logout");
    format_output("0. Exit");
    int choice;
    cin >> choice;
    switch (choice) {
    case 0: {
        EXIT_CODE = true;
        break;
    }
    case 1: {
        Course::show_timetable();
        break;
    }
    case 2: {
        Attendance::show_attendance(current_user->get_username());
        break;
    }
    case 3: {
        Course::show_user_courses(current_user->get_year());
        break;
    }
    case 4: {
        cout << "Do you really want to logout? (y/n)\n";
        char in;
        cin >> in;
        if (in=='y' || in=='Y') {
            START = true;
            current_user = new AnonymousUser;
            break;
        }
        else {
            break;
        }
    }
    default:break;
    }
}

void AdminDetailView::display()
{
    string header = "Welcome "+current_user->get_fullname();
    format_output(header);
    format_output("1. Create new user");
    format_output("2. Delete a user");
    format_output("3. Create new course");
    format_output("4. Delete a course");
    format_output("5. Show course list");
    format_output("6. Show timetable");
    format_output("7. Update timetable");
    format_output("8. Update attendance");
    format_output("9. View attendance");
    format_output("10. Logout");
    format_output("0. Exit");
    int choice;
    //cin.ignore();
    cin >> choice;
    switch (choice) {
    case 0: {
        EXIT_CODE = true;
        break;
    }
    case 1: {
        view_choice = VIEW_CHOICES(REGISTER);
        break;
    }
    case 2: {
        cout << "Enter username:\n";
        string username;
        cin >> username;
        if (User::all().find(username)!=User::all().end()) {
            auto user = User::all().find(username)->second;
            bool erased = user.remove();
            if (erased) {
                cout << user.get_fullname() << " deleted.\n";
                cout << "Now there are " << user.all().size() << " users in the system \n";
            }
        }
        else cout << "User doesn't exist.\n";
        break;
    }
    case 3: {
        rootrestart:
        cout << "Enter Course name: \n";
        string name, username;
        int year;
        char slot;
        cin.ignore();
        getline(cin, name);
        reenter_slot_year:
        int flag = 0;
        cout << "Enter slot(A-F), year: \n";
        cin >> slot >> year;
        for (auto& i : Course::all()) {
            Course temp = i.second;
            if (temp.get_course_name()==name) {
                flag = 1;
            }
            else if (temp.get_slot()==slot && temp.get_year()==year) {
                flag = 2;
            }
        }
        if (flag==1) {
            cout << "Course already exists!\n";
            goto reenter_slot_year;
        }
        if (flag==2) {
            cout << "A course already exists in the given slot for the given year!\n";
            goto reenter_slot_year;
        }
        reenter_username:
        cout << "Enter instructor's username: \n";
        cin >> username;
        if (User::all().find(username)!=User::all().end() && User::all().find(username)->second.is_superuser()) {
            Course course(name, slot, username, year);
            try {
                course.save();
                cout << course.get_course_name() << " successfully registered.\n";
            }
            catch (CourseError& e) {
                cout << e.print_error() << endl;
                goto rootrestart;
            }
        }
        else {
            cin.ignore();
            cout << "Enter a valid username \n";
            goto reenter_username;
        }
        break;
    }
    case 4: {
        cout << "Enter a course number to delete from list: \n";
        int j = 1;
        for (auto& i:Course::all()) {
            cout << j++ << ". " << i.second.get_course_name() << endl;
        }
        int ch;
        cin >> ch;
        auto it = Course::all().begin();
        advance(it, ch-1);
        if (it!=Course::all().end()) {
            Course temp = it->second;
            temp.remove();
            cout << temp.get_course_name() << " deleted successfully.\n";
        }
        break;
    }
    case 5: {
        cout << "List of all courses: \n";
        int j = 1;
        for (auto& i:Course::all()) {
            cout << j++ << ". " << i.second.get_course_name() << endl;
        }
        break;
    }
    case 6: {
        Course::show_timetable();
        break;
    }
    case 7: {
        cout << "Enter 24 slot values, 4periods x 6weeks each: \n";
        Course::update_timetable();
        break;
    }
    case 8: {
        cout << "Enter username, course, present status(0,1): \n";
        string username, course;
        bool is_present;
        cin >> username >> course >> is_present;
        Attendance::update_attendance(username, course, is_present);
        break;
    }
    case 9: {
        cout << "Enter the course name to view the attendance: \n";
        string course;
        cin >> course;
        Attendance::show_attendance_course(course);
        break;
    }
    case 10: {
        cout << "Do you really want to logout? (y/n)\n";
        char in;
        cin >> in;
        if (in=='y' || in=='Y') {
            START = true;
            current_user = new AnonymousUser;
            break;
        }
        else {
            break;
        }
    }
    default:break;
    }
}
